#ifndef SUBORBITAL_PYTHON_EVENT_HPP
#define SUBORBITAL_PYTHON_EVENT_HPP

#include <Python/Python.h>

#include <suborbital/event/Event.hpp>

namespace suborbital
{
    class PythonEvent : public Event
    {
    public:
        /**
         * Constructor.
         */
        PythonEvent();

        /**
         * Destructor.
         */
        virtual ~PythonEvent();

    public:
        /**
         * The Python object that was created when constructing classes that derive from this class.
         *
         * You really don't want to touch this!
         */
        PyObject* m_derived;
    };
}

#endif