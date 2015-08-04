#ifndef SUBORBITAL_EVENT_CALLBACK
#define SUBORBITAL_EVENT_CALLBACK

#include <cassert>
#include <memory>
#include <functional>

#include <suborbital/event/EventCallbackBase.hpp>

namespace suborbital
{
    template<typename EventType>
    class EventCallback : public EventCallbackBase
    {
    public:
        /**
         * Constructor.
         *
         * @param callback_function Callback function for the event.
         */
        EventCallback(const std::function<void(std::shared_ptr<EventType>)>& callback_function)
        : EventCallbackBase()
        , m_callback_function(callback_function)
        {
            // Nothing to do.
        }

        /**
         * Copy constructor.
         *
         * @param other The event callback to copy from.
         */
        EventCallback(const EventCallback<EventType>& other)
        : m_callback_function(other.m_callback_function)
        {
            // Nothing to do.
        }

        /**
         * Copy assignment operator.
         *
         * @param other The event callback to copy from.
         */
        EventCallback<EventType>& operator=(const EventCallback<EventType>& other)
        {
            m_callback_function = other.m_callback_function;
            return *this;
        }

        /**
         * Destructor.
         */
        ~EventCallback()
        {
            // Nothing to do.
        }

        /**
         * Executes the callback function.
         */
        void operator()(std::shared_ptr<Event> event)
        {
            std::shared_ptr<EventType> derived_event = std::dynamic_pointer_cast<EventType>(event);
            assert(derived_event != nullptr);

            m_callback_function(derived_event);
        }

    private:
        /**
         * The event callback function being wrapped.
         */
        std::function<void(std::shared_ptr<EventType>)> m_callback_function;
    };
}

#endif