#include <cassert>
#include <iostream>

#include <suborbital/event/EventSubscription.hpp>
#include <suborbital/event/EventDispatcher.hpp>

namespace suborbital
{
    EventSubscription::EventSubscription(watch_ptr<EventDispatcher> dispatcher, const std::string& event_name, std::size_t callback_index)
    : m_cancelled(false)
    , m_dispatcher(dispatcher)
    , m_event_name(event_name)
    , m_callback_index(callback_index)
    {
        std::cout << "EventSubscription::EventSubscription()" << std::endl;
    }

    EventSubscription::~EventSubscription()
    {
        std::cout << "EventSubscription::~EventSubscription()" << std::endl;

        if (active())
        {
            unsubscribe();
        }
    }

    bool EventSubscription::active() const
    {
        return m_cancelled == false && m_dispatcher;
    }

    void EventSubscription::unsubscribe()
    {
        assert(m_cancelled == false);

        if (m_dispatcher)
        {
            m_dispatcher->unsubscribe(*this);
        }

        m_cancelled = true;
    }
}