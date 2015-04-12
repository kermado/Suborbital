#ifndef SUBORBITAL_EVENT_SUBSCRIPTION_HPP
#define SUBORBITAL_EVENT_SUBSCRIPTION_HPP

#include <string>

#include <suborbital/NonCopyable.hpp>
#include <suborbital/WatchPtr.hpp>
#include "EventDispatcher.hpp"

namespace suborbital
{
    // Forward declarations.
    class EventDispatcher;

    /**
     * Manages the lifetime of an event subscription.
     *
     * The handled event subscription is cancelled automatically upon destruction. Alternatively, the subscription can
     * be manually cancelled by calling `unsubscribe`.
     */
    class EventSubscription : private NonCopyable
    {
    friend EventDispatcher;
    public:
        /**
         * Destructor.
         *
         * Cancels the event subscription automatically.
         */
        ~EventSubscription();

        /**
         * Whether the subscription is active.
         *
         * @return True if the subscription is still active.
         */
        bool active() const;

        /**
         * Cancels the event subscription.
         */
        void unsubscribe();

    private:
        /**
         * Constructor.
         */
        EventSubscription(EventDispatcher* dispatcher, const std::string& event_name);

    private:
        /**
         * Pointer to the dispatcher for the subscription. Will be a nullptr if the subscription has been cancelled.
         */
        EventDispatcher* m_dispatcher;

        /**
         * The name of the event that the subscription is for.
         */
        std::string m_event_name;
    };
}

#endif