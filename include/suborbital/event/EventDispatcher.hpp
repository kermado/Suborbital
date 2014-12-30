#ifndef SUBORBITAL_EVENT_DISPATCHER_HPP
#define SUBORBITAL_EVENT_DISPATCHER_HPP

#include <memory>
#include <functional>
#include <vector>
#include <unordered_map>

#include <suborbital/NonCopyable.hpp>
#include <suborbital/Watchable.hpp>

namespace suborbital
{
    // Forward declarations.
    class Event;
    class EventSubscription;
    class EventCallbackBase;

    /**
     * Event dispatcher.
     */
    class EventDispatcher : public Watchable, private NonCopyable
    {
    friend EventSubscription;
    public:
        /**
         * Constructor.
         */
        EventDispatcher();

        /**
         * Destructor.
         */
        ~EventDispatcher();

        /**
         * Publishes an event to be dispatched to all subscribers of the specified `event_name`.
         *
         * @param event_name Name of the event to publish.
         * @param Shared pointer to the event to be published.
         */
        void publish(const std::string& event_name, std::shared_ptr<Event> event);

        /**
         * Subscribes to receive events of the specified `event_name`.
         *
         * @param event_name Name of the event to subscribe for.
         * @param callback Callback function that should receive the events.
         * @return Subscription object that controls the lifetime of the subscription.
         */
        std::unique_ptr<EventSubscription> subscribe(const std::string& event_name, std::unique_ptr<EventCallbackBase> callback);

    private:
        /**
         * Cancels a subscription.
         *
         * This method cannot be called directly. See the `EventSubscription` class for details on how to unsubscribe
         * for events.
         */
        void unsubscribe(EventSubscription& subscription);

    private:
        /**
         * Event subscriptions.
         *
         * Maps event names to a vector of callback functions.
         */
        std::unordered_map<std::string, std::vector<std::unique_ptr<EventCallbackBase>>> m_subscriptions;
    };
}

#endif