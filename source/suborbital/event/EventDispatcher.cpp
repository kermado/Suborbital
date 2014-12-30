#include <cassert>
#include <iostream>

#include <suborbital/event/Event.hpp>
#include <suborbital/event/EventDispatcher.hpp>
#include <suborbital/event/EventSubscription.hpp>
#include <suborbital/event/EventCallbackBase.hpp>

namespace suborbital
{
    EventDispatcher::EventDispatcher()
    : m_subscriptions()
    {
        std::cout << "EventDispatcher::EventDispatcher()" << std::endl;
    }

    EventDispatcher::~EventDispatcher()
    {
        std::cout << "EventDispatcher::~EventDispatcher()" << std::endl;
    }

    void EventDispatcher::publish(const std::string& event_name, std::shared_ptr<Event> event)
    {
        auto iter = m_subscriptions.find(event_name);
        if (iter != m_subscriptions.end())
        {
            for (std::unique_ptr<EventCallbackBase>& callback : iter->second)
            {
                (*callback)(event);
            }
        }
    }

    std::unique_ptr<EventSubscription> EventDispatcher::subscribe(const std::string& event_name, std::unique_ptr<EventCallbackBase> callback)
    {
        std::vector<std::unique_ptr<EventCallbackBase>>& callbacks = m_subscriptions[event_name];
        const std::size_t insertion_index = callbacks.size();
        callbacks.push_back(std::move(callback));

        return std::unique_ptr<EventSubscription>(new EventSubscription(watch_ptr<EventDispatcher>(this), event_name, insertion_index));
    }

    void EventDispatcher::unsubscribe(EventSubscription& subscription)
    {
        assert(subscription.active() == true);

        auto iter = m_subscriptions.find(subscription.m_event_name);
        assert (iter != m_subscriptions.end());

        std::vector<std::unique_ptr<EventCallbackBase>>& callbacks = iter->second;
        callbacks.erase(callbacks.begin() + subscription.m_callback_index);
    }
}