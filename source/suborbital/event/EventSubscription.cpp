#include <cassert>

#include <suborbital/event/EventSubscription.hpp>
#include <suborbital/event/EventDispatcher.hpp>

namespace suborbital
{
    EventSubscription::EventSubscription(EventDispatcher* dispatcher, const std::string& event_name)
    : m_dispatcher(dispatcher)
    , m_event_name(event_name)
    {
        // Nothing to do.
    }

    EventSubscription::~EventSubscription()
    {
        unsubscribe();
    }

    bool EventSubscription::active() const
    {
        return m_dispatcher != nullptr;
    }

    void EventSubscription::unsubscribe()
    {
        assert(m_dispatcher != nullptr);

        m_dispatcher->unsubscribe(this);
        m_dispatcher = nullptr;
    }
}