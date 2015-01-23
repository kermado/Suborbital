#ifndef SUBORBITAL_PYTHON_SYSTEM_FACTORY_HPP
#define SUBORBITAL_PYTHON_SYSTEM_FACTORY_HPP

#include <string>
#include <iostream>

#include <suborbital/PythonRuntime.hpp>

#include <suborbital/system/SpecificSystemFactory.hpp>
#include <suborbital/system/PythonSystem.hpp>

namespace suborbital
{
    template<>
    class SpecificSystemFactory<PythonSystem> : public SystemFactory
    {
    public:
        /**
         * Constructor.
         *
         * @param class_name Class/file name for the system to be instantiated by the `create` function.
         */
        SpecificSystemFactory(const std::string& class_name)
        : m_class_name(class_name)
        {
            // Nothing to do.
        }

        /**
         * Destructor.
         */
        ~SpecificSystemFactory() = default;

        /**
         * Instantiates the Python defined system and returns a unique_ptr to the created system.
         *
         * This function will return a nullptr in the event that the Python system could not be instantiated.
         *
         * @return Unique pointer to the created Python system.
         */
        std::unique_ptr<System> create() const
        {
            // Import the script file.
            PyObject* module = PyImport_ImportModule(m_class_name.c_str());
            if (module == NULL)
            {
                std::cerr << "Failed to import Python module \"" << m_class_name << "\"" << std::endl;
                PyErr_Print();
                return nullptr;
            }

            // Get the class definition.
            PyObject* python_class = PyObject_GetAttrString(module, m_class_name.c_str());
            if (python_class == NULL)
            {
                std::cerr << "Failed to find " << m_class_name <<  " class definition in Python module \""
                          << m_class_name << "\"" << std::endl;
                PyErr_Print();
                return nullptr;
            }

            // Create a new instance of the class.
            PyObject* python_instance = PyObject_CallFunctionObjArgs(python_class, NULL);
            if (python_instance == NULL)
            {
                std::cerr << "Failed to instantiate " << m_class_name << " class in Python module \""
                          << m_class_name << "\"" << std::endl;
                PyErr_Print();
                return nullptr;
            }

            // Tell the Python interpreter to disown the object so that we can take charge of its lifetime.
            PyObject* python_disown_function = PyObject_GetAttrString(python_instance, "__disown__");
            if (python_disown_function == NULL)
            {
                std::cerr << "Failed find __disown__ member function on instance of " << m_class_name << std::endl;
                PyErr_Print();
                return nullptr;
            }

            PyObject* python_disown_result = PyObject_CallFunctionObjArgs(python_disown_function, NULL);
            if (python_disown_result == NULL)
            {
                std::cerr << "Call to __disown__ failed on instance of " << m_class_name << std::endl;
                PyErr_Print();
                return nullptr;
            }

            // Now we must convert the PyObject pointer into our PythonSystem pointer.
            void* converted_ptr = NULL;
            swig_type_info* system_type_info = SWIG_TypeQuery("suborbital::PythonSystem*");
            const int status = SWIG_ConvertPtr(python_instance, &converted_ptr, system_type_info, 0);
            if (!SWIG_IsOK(status))
            {
                std::cerr << "Failed to convert Python object to a PythonSystem for class " << m_class_name
                          << std::endl;
                return nullptr;
            }

            PythonSystem* scripted_system_ptr = reinterpret_cast<PythonSystem*>(converted_ptr);

            // Store the PyObject* that was created when constructing our PythonSystem derived types so that we can
            // easily return it when scripts request to access scripted system types.
            //
            // Thanks to Flexo:
            // http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
            scripted_system_ptr->instance(python_instance);

            // Decrease reference counts for created python objects.
            Py_XDECREF(python_disown_function);
            Py_XDECREF(python_disown_result);
            Py_XDECREF(python_instance);
            Py_XDECREF(python_class);

            // Return a unique pointer to the scripted Python system.
            return std::unique_ptr<PythonSystem>(scripted_system_ptr);
        }

    private:
        /**
         * Class/file name for the Python defined system.
         */
        std::string m_class_name;
    };
}

#endif