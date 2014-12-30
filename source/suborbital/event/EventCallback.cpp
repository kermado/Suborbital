#include <suborbital/event/EventCallback.hpp>

namespace suborbital
{
    EventCallback::EventCallback(const std::function<void(std::shared_ptr<Event>)>& callback_function)
    : EventCallbackBase()
    , m_callback_function(callback_function)
    {
        // Nothing to do.
    }

    EventCallback::EventCallback(const EventCallback& other)
    : m_callback_function(other.m_callback_function)
    {
        // Nothing to do.
    }

    EventCallback& EventCallback::operator=(const EventCallback& other)
    {
        m_callback_function = other.m_callback_function;
        return *this;
    }

    EventCallback::~EventCallback()
    {
        // Nothing to do.
    }

    void EventCallback::operator()(std::shared_ptr<Event> event)
    {
        m_callback_function(event);
    }
}