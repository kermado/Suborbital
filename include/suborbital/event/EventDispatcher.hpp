#ifndef SUBORBITAL_EVENT_DISPATCHER_HPP
#define SUBORBITAL_EVENT_DISPATCHER_HPP

#include <string>
#include <memory>
#include <functional>
#include <map>
#include <unordered_map>

#include <suborbital/NonCopyable.hpp>
#include <suborbital/Watchable.hpp>

namespace suborbital
{
    // Forward declarations.
    class Event;
    class EventSubscription;
    class EventCallbackBase;

    // Type definitions.
    namespace
    {
        /**
         * Map from event subscriptions to callbacks.
         *
         * Note that we map from `EventSubscription` pointers since subscriptions are unique and non-copyable.
         */
        typedef std::map<EventSubscription* const, std::unique_ptr<EventCallbackBase>> SubscriptionMap;
    }

    /**
     * Event dispatcher.
     *
     * Manages subscriptions for events and provides methods for both subscribing to receive named events and publishing
     * events to all registered subscribers.
     *
     * Note that we make no guarantees on the derived type of `Event`. The `publish` function delivers the provided
     * event shared pointer to all objects that are subscribed to the provided event name. The scripting system requires
     * that the event name matches the derived event's class name exactly in order for type casting to function
     * correctly. For example, to subscribe for events of type `SomeEvent`, you must use the event name "SomeEvent".
     * This is the case for event classes defined in both C++ and Python. You can include the scope resolution operator
     * for C++ defined event classes under specific namespaces; for example "mynamespace::SomeEvent".
     *
     * It is the responsibility of any C++ defined callback functions to cast the received event shared pointer to the
     * correct type. Event type inference is handled automatically by the scripting system for Python defined callback
     * functions.
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
         * This function is called exclusively by the `EventSubscription` class. See the `EventSubscription` class for
         * details on how to unsubscribe for events.
         *
         * @param subscription Pointer to the subscription that is being cancelled.
         */
        void unsubscribe(EventSubscription* subscription);

    private:
        /**
         * Event subscriptions.
         *
         * Maps event names to a map from event subscriptions to callback pointers.
         */
        std::unordered_map<std::string, SubscriptionMap> m_subscriptions;
    };
}

#endif