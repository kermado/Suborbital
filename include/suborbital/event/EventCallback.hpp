#ifndef SUBORBITAL_EVENT_CALLBACK
#define SUBORBITAL_EVENT_CALLBACK

#include <memory>
#include <functional>

#include <suborbital/event/EventCallbackBase.hpp>

namespace suborbital
{
    /**
     * Event callback function.
     */
    class EventCallback : public EventCallbackBase
    {
    public:
        /**
         * Constructor.
         *
         * @param callback_function Callback function for the event.
         */
        EventCallback(const std::function<void(std::shared_ptr<Event>)>& callback_function);

        /**
         * Copy constructor.
         *
         * @param other The event callback to copy from.
         */
        EventCallback(const EventCallback& other);

        /**
         * Copy assignment operator.
         *
         * @param other The event callback to copy from.
         */
        EventCallback& operator=(const EventCallback& other);

        /**
         * Destructor.
         */
        ~EventCallback();

        /**
         * Executes the callback function.
         */
        void operator()(std::shared_ptr<Event> event);

    private:
        /**
         * The event callback function being wrapped.
         */
        std::function<void(std::shared_ptr<Event>)> m_callback_function;
    };
}

#endif