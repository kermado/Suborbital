#include <suborbital/PythonRuntime.hpp>
#include <suborbital/event/PythonEventCallback.hpp>
#include <suborbital/event/PythonEvent.hpp>

namespace suborbital
{
    PythonEventCallback::PythonEventCallback(PyObject* callback_function)
    : EventCallbackBase()
    , m_callback_function(callback_function)
    {
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
        std::shared_ptr<PythonEvent> python_event = std::dynamic_pointer_cast<PythonEvent>(event);
        if (python_event)
        {
            PyObject* derived_instance = python_event->instance();
            assert(derived_instance != nullptr);
            PyObject_CallFunctionObjArgs(m_callback_function, derived_instance, NULL);
        }
        else
        {
            swig_type_info* event_type_info = SWIG_TypeQuery("std::shared_ptr<suborbital::Event>*");
            assert(event_type_info != NULL);
            PyObject* python_event_object = SWIG_NewPointerObj((void*) &event, event_type_info, 0);
            PyObject_CallFunctionObjArgs(m_callback_function, python_event_object, NULL);
        }
    }
}