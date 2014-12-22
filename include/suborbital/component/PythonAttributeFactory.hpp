#ifndef SUBORBITAL_PYTHON_ATTRIBUTE_FACTORY_HPP
#define SUBORBITAL_PYTHON_ATTRIBUTE_FACTORY_HPP

#include <suborbital/PythonRuntime.hpp>
#include <suborbital/component/AttributeFactory.hpp>
#include <suborbital/component/PythonAttribute.hpp>

namespace suborbital
{
    template<>
    class AttributeFactory<PythonAttribute> : public ComponentFactory
    {
    public:
        AttributeFactory(const std::string& class_name)
        : m_class_name(class_name)
        {
            // Nothing to do.
        }

        ~AttributeFactory()
        {
            // Nothing to do.
        }

        std::unique_ptr<Component> create() const
        {
            assert(Py_IsInitialized());

            // Import the script file.
            PyObject* module = PyImport_ImportModule(m_class_name.c_str());
            if (module == NULL)
            {
                PyErr_Print();
                return nullptr;
            }

            // Get the class definition.
            PyObject* python_class = PyObject_GetAttrString(module, m_class_name.c_str());
            if (python_class == NULL)
            {
                PyErr_Print();
                return nullptr;
            }

            // Create a new instance of the class.
            PyObject* python_instance = PyObject_CallFunctionObjArgs(python_class, NULL);
            if (python_instance == NULL)
            {
                PyErr_Print();
                return nullptr;
            }

            // Tell the Python interpreter to disown the object so that we can take charge of its lifetime.
            PyObject* python_disown_function = PyObject_GetAttrString(python_instance, "__disown__");
            if (python_disown_function == NULL)
            {
                PyErr_Print();
                return nullptr;
            }

            PyObject* python_disown_result = PyObject_CallFunctionObjArgs(python_disown_function, NULL);
            if (python_disown_result == NULL)
            {
                PyErr_Print();
                return nullptr;
            }

            // Now we must convert the PyObject pointer into our PythonAttribute pointer.
            void* converted_ptr = NULL;
            swig_type_info* attribute_type_info = SWIG_TypeQuery("behaviour::PythonAttribute*");
            const int status = SWIG_ConvertPtr(python_instance, &converted_ptr, attribute_type_info, 0);
            if (!SWIG_IsOK(status))
            {
                std::cerr << "Failed to convert Python object to a PythonAttribute for class " << m_class_name
                          << std::endl;
                return nullptr;
            }

            PythonAttribute* scripted_attribute_ptr = reinterpret_cast<PythonAttribute*>(converted_ptr);

            // Store the PyObject* that was created when constructing our PythonAttribute derived types so that we can
            // easily return it when scripts request to access scripted attribute types.
            //
            // Thanks to Flexo:
            // http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
            scripted_attribute_ptr->derived = python_instance;

            // Decrease reference counts for created python objects.
            Py_XDECREF(python_disown_function);
            Py_XDECREF(python_disown_result);
            Py_XDECREF(python_instance);
            Py_XDECREF(python_class);

            // Return a unique pointer to the scripted Python attribute.
            return std::unique_ptr<PythonAttribute>(scripted_attribute_ptr);
        }

    private:
        std::string m_class_name;
    };
}

#endif
