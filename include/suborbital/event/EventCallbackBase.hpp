#ifndef SUBORBITAL_EVENT_CALLBACK_BASE_HPP
#define SUBORBITAL_EVENT_CALLBACK_BASE_HPP

#include <memory>

namespace suborbital
{
    // Forward declarations.
    class Event;

    /**
     * The base class for event callback function wrappers.
     */
    class EventCallbackBase
    {
    public:
        /**
         * Destructor.
         */
        virtual ~EventCallbackBase();

        /**
         * Call operator.
         *
         * Executes the wrapped callback function, passing in the specified `event`.
         *
         * @param event Shared pointer to the event that is handled by the wrapped callback function.
         */
        virtual void operator()(std::shared_ptr<Event> event) = 0;

    protected:
        /**
         * Constructor.
         */
        EventCallbackBase();
    };
}

#endif