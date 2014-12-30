#ifndef SUBORBITAL_PYTHON_EVENT_HPP
#define SUBORBITAL_PYTHON_EVENT_HPP

#include <suborbital/PythonObject.hpp>
#include <suborbital/event/Event.hpp>

namespace suborbital
{
    class PythonEvent : public PythonObject, public Event
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
    };
}

#endif