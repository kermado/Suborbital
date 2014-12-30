#ifndef SUBORBITAL_EVENT_HPP
#define SUBORBITAL_EVENT_HPP

namespace suborbital
{
    /**
     * The base class for all events.
     */
    class Event
    {
    public:
        /**
         * Destructor.
         */
        virtual ~Event();

    protected:
        /**
         * Constructor.
         */
        Event();
    };
}

#endif