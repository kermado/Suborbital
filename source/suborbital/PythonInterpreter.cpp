#include <cassert>
#include <iostream>
#include <Python/Python.h>

#include <suborbital/PythonInterpreter.hpp>
#include <suborbital/component/PythonBehaviour.hpp>

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
}