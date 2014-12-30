#ifndef SUBORBITAL_PYTHON_EVENT_CALLBACK_HPP
#define SUBORBITAL_PYTHON_EVENT_CALLBACK_HPP

#include <Python/Python.h>

#include <suborbital/event/EventCallbackBase.hpp>

namespace suborbital
{
    class PythonEventCallback : public EventCallbackBase
    {
    public:
        /**
         * Constructor.
         *
         * @param callback_function Python function object.
         */
        PythonEventCallback(PyObject* callback_function);

        /**
         * Copy constructor.
         *
         * @param other The Python event callback to copy from.
         */
        PythonEventCallback(const PythonEventCallback& other);

        /**
         * Destructor.
         */
        ~PythonEventCallback();

        /**
         * Copy assignment operator.
         *
         * @param other The Python event callback to copy from.
         */
        PythonEventCallback& operator=(const PythonEventCallback& other);

        /**
         * Executes the Python callback function.
         */
        void operator()(std::shared_ptr<Event> event);

    private:
        /**
         * Python callback function object.
         */
        PyObject* m_callback_function;
    };
}

#endif