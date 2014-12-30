#include <iostream>

#include <suborbital/PythonRuntime.hpp>
#include <suborbital/event/PythonEventCallback.hpp>

namespace suborbital
{
    PythonEventCallback::PythonEventCallback(PyObject* callback_function)
    : EventCallbackBase()
    , m_callback_function(callback_function)
    {
        std::cout << "PythonEventCallback::PythonEventCallback()" << std::endl;

        assert(m_callback_function != nullptr);
        assert(m_callback_function != Py_None);
        assert(PyCallable_Check(m_callback_function));

        Py_INCREF(m_callback_function);
    }

    PythonEventCallback::PythonEventCallback(const PythonEventCallback& other)
    : m_callback_function(other.m_callback_function)
    {
        Py_INCREF(m_callback_function);
    }

    PythonEventCallback::~PythonEventCallback()
    {
        std::cout << "PythonEventCallback::~PythonEventCallback()" << std::endl;

        Py_DECREF(m_callback_function);
    }

    PythonEventCallback& PythonEventCallback::operator=(const PythonEventCallback& other)
    {
        if (m_callback_function != nullptr)
        {
            Py_DECREF(m_callback_function);
        }

        m_callback_function = other.m_callback_function;
        Py_INCREF(m_callback_function);

        return *this;
    }

    void PythonEventCallback::operator()(std::shared_ptr<Event> event)
    {
        swig_type_info* event_type_info = SWIG_TypeQuery("std::shared_ptr<suborbital::Event>*");
        assert(event_type_info != NULL);
        PyObject* python_event_object = SWIG_NewPointerObj((void*) &event, event_type_info, 0);
        PyObject_CallFunctionObjArgs(m_callback_function, python_event_object, NULL);
    }
}