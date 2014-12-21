#ifndef SUBORBITAL_BEHAVIOUR_FACTORY_HPP
#define SUBORBITAL_BEHAVIOUR_FACTORY_HPP

#include <string>
#include <memory>
#include <iostream>

#include <Python/Python.h>

#include <suborbital/Behaviour.hpp>
#include <suborbital/PythonBehaviour.hpp>

#include "SwigRuntime.h"

namespace suborbital
{
    class IBehaviourFactory
    {
    public:
        IBehaviourFactory()
        {
            // Nothing to do.
        }

        virtual ~IBehaviourFactory()
        {
            // Nothing to do.
        }

        virtual std::unique_ptr<Behaviour> create() const = 0;
    };

    template<typename BehaviourType>
    class BehaviourFactory : public IBehaviourFactory
    {
    public:
        BehaviourFactory();
        ~BehaviourFactory();

        std::unique_ptr<Behaviour> create() const
        {
            static_assert(std::is_base_of<Behaviour, BehaviourType>::value,
                    "Template parameter BehaviourType in BehaviourFactory is not derived from Behaviour");
            return std::unique_ptr<BehaviourType>(new BehaviourType());
        }
    };

    template<>
    class BehaviourFactory<PythonBehaviour> : public IBehaviourFactory
    {
    public:
        BehaviourFactory(const std::string& class_name)
        : m_class_name(class_name)
        {
            // Nothing to do.
        }

        ~BehaviourFactory()
        {
            // Nothing to do.
        }

        std::unique_ptr<Behaviour> create() const
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

            // Now we must convert the PyObject pointer into our PythonBehaviour pointer.
            void* converted_ptr = NULL;
            swig_type_info* behaviour_type_info = SWIG_TypeQuery("behaviour::PythonBehaviour*");
            const int status = SWIG_ConvertPtr(python_instance, &converted_ptr, behaviour_type_info, 0);
            if (!SWIG_IsOK(status))
            {
                std::cerr << "Failed to convert Python object to a PythonBehaviour for class " << m_class_name
                          << std::endl;
                return nullptr;
            }

            PythonBehaviour* scripted_behaviour_ptr = reinterpret_cast<PythonBehaviour*>(converted_ptr);

            // Store the PyObject* that was created when constructing our PythonBehaviour derived types so that we can
            // easily return it when scripts request to access scripted behaviour types.
            //
            // Thanks to Flexo:
            // http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
            scripted_behaviour_ptr->derived = python_instance;

            // Decrease reference counts for created python objects.
            Py_XDECREF(python_disown_function);
            Py_XDECREF(python_disown_result);
            Py_XDECREF(python_instance);
            Py_XDECREF(python_class);

            // Return a unique pointer to the scripted behaviour.
            return std::unique_ptr<Behaviour>(scripted_behaviour_ptr);
        }

    private:
        std::string m_class_name;
    };
}

#endif