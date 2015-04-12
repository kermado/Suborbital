#include <cassert>

#include <suborbital/event/Event.hpp>
#include <suborbital/event/EventDispatcher.hpp>
#include <suborbital/event/EventSubscription.hpp>
#include <suborbital/event/EventCallbackBase.hpp>

namespace suborbital
{
    EventDispatcher::EventDispatcher()
    : m_subscriptions()
    {
        // Nothing to do.
    }

    EventDispatcher::~EventDispatcher()
    {
        for (const auto& event_name_subscriptions : m_subscriptions)
        {
            const auto& subscription_callbacks = event_name_subscriptions.second;
            for (const auto& subscription_callback : subscription_callbacks)
            {
                EventSubscription* subscription = subscription_callback.first;
                subscription->unsubscribe();
            }
        }
    }

    void EventDispatcher::publish(const std::string& event_name, std::shared_ptr<Event> event)
    {
        auto iter = m_subscriptions.find(event_name);
        if (iter != m_subscriptions.end())
        {
            for (auto& subscription_callback : iter->second)
            {
                (*subscription_callback.second)(event);
            }
        }
    }

    std::unique_ptr<EventSubscription> EventDispatcher::subscribe(const std::string& event_name, std::unique_ptr<EventCallbackBase> callback)
    {
        EventSubscription* subscription = new EventSubscription(this, event_name);
        auto& callbacks = m_subscriptions[event_name];
        callbacks.insert(std::make_pair(subscription, std::move(callback)));

        return std::unique_ptr<EventSubscription>(subscription);
    }

    void EventDispatcher::unsubscribe(EventSubscription* subscription)
    {
        assert(subscription->active() == true);

        auto iter = m_subscriptions.find(subscription->m_event_name);
        assert (iter != m_subscriptions.end());

        std::size_t removed = iter->second.erase(subscription);
        assert(removed == 1);
    }
}