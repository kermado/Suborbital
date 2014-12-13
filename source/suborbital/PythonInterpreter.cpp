#include <cassert>
#include <iostream>
#include <Python.h>

#include <suborbital/PythonInterpreter.hpp>
#include <suborbital/component/PythonComponent.hpp>

#include "SwigRuntime.h"

namespace suborbital
{
    PythonInterpreter::PythonInterpreter()
    : m_search_paths()
    {
        // Initialize the Python interpreter.
        // This initializes the table of loaded modules (sys.modules) and creates the fundamental modules __builtin__,
        // __main__ and sys. It also initializes the module search path (sys.path).
        Py_Initialize();
    }

    PythonInterpreter::~PythonInterpreter()
    {
        // Destroy the Python interpreter, freeing all memory allocated.
        Py_Finalize();
    }

    void PythonInterpreter::add_path(const std::string& path)
    {
        auto insertion = m_search_paths.insert(path);
        if (insertion.second)
        {
            PyObject* sys = PyImport_ImportModule("sys");
            PyObject* sys_path_list = PyObject_GetAttrString(sys, "path");
            const int error = PyList_Append(sys_path_list, PyString_FromString(path.c_str()));
            if (error) PyErr_Print();
        }
    }

    std::unique_ptr<component::Component> PythonInterpreter::create(const std::string& class_name) const
    {
        // Import the script file.
        PyObject* module = PyImport_ImportModule(class_name.c_str());
        if (!module) PyErr_Print();

        // Get the class definition.
        PyObject* python_class = PyObject_GetAttrString(module, class_name.c_str());
        if (!python_class) PyErr_Print();

        // Create a new instance of the class.
        PyObject* python_instance = PyObject_CallFunctionObjArgs(python_class, NULL);
        if (!python_instance) PyErr_Print();

        // Tell the Python interpreter to disown the object so that we can take charge of its lifetime.
        PyObject_CallFunctionObjArgs(PyObject_GetAttrString(python_instance, "__disown__"), NULL);

        // Now we must convert the PyObject pointer into our PythonComponent pointer.
        void* converted_ptr = 0;
        swig_type_info* component_type_info = SWIG_TypeQuery("component::PythonComponent*");
        const int status = SWIG_ConvertPtr(python_instance, &converted_ptr, component_type_info, 0);
        if (!SWIG_IsOK(status))
        {
            std::cerr << "Failed to convert Python object to a PythonComponent for class " << class_name << std::endl;
            return nullptr;
        }
        component::PythonComponent* scripted_component_ptr = reinterpret_cast<component::PythonComponent*>(converted_ptr);

        // Store the PyObject* that was created when constructing our PythonComponent derived types so that we can
        // easily return it when scripts request to access scripted component types.
        //
        // Thanks to Flexo:
        // http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
        scripted_component_ptr->derived = python_instance;

        // Decrease reference counts for created python objects.
        Py_XDECREF(python_instance);
        Py_XDECREF(python_class);

        // Return a unique pointer to the scripted component.
        return std::unique_ptr<component::Component>(scripted_component_ptr);
    }
}