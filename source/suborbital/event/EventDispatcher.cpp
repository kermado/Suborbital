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
        // Nothing to do.
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
        EventSubscription* subscription = new EventSubscription(shared_from_this(), event_name);
        auto& callbacks = m_subscriptions[event_name];
        callbacks.insert(std::make_pair(subscription, std::move(callback)));

        return std::unique_ptr<EventSubscription>(subscription);
    }

    void EventDispatcher::unsubscribe(EventSubscription* subscription)
    {
        assert(subscription->active() == true);

        auto iter = m_subscriptions.find(subscription->m_event_name);
        assert (iter != m_subscriptions.end());

        auto& callbacks = iter->second;
        auto subscription_record = callbacks.find(subscription);
        assert(subscription_record != callbacks.end());

        callbacks.erase(subscription);
    }
}