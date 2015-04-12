#include <cassert>

#include <suborbital/event/EventSubscription.hpp>
#include <suborbital/event/EventDispatcher.hpp>

namespace suborbital
{
    EventSubscription::EventSubscription(std::weak_ptr<EventDispatcher> dispatcher, const std::string& event_name)
    : m_cancelled(false)
    , m_dispatcher(dispatcher)
    , m_event_name(event_name)
    {
        // Nothing to do.
    }

    EventSubscription::~EventSubscription()
    {
        if (m_cancelled == false)
        {
            unsubscribe();
        }
    }

    bool EventSubscription::active() const
    {
        return m_cancelled == false && m_dispatcher.lock();
    }

    void EventSubscription::unsubscribe()
    {
        assert(m_cancelled == false);

        if (std::shared_ptr<EventDispatcher> dispatcher = m_dispatcher.lock())
        {
            dispatcher->unsubscribe(this);
        }

        m_cancelled = true;
    }
}