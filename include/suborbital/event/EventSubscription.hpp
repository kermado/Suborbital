#ifndef SUBORBITAL_EVENT_SUBSCRIPTION_HPP
#define SUBORBITAL_EVENT_SUBSCRIPTION_HPP

#include <string>
#include <memory>

#include <suborbital/NonCopyable.hpp>

namespace suborbital
{
    // Forward declarations.
    class EventDispatcher;

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
        EventSubscription(std::weak_ptr<EventDispatcher> dispatcher, const std::string& event_name);

    private:
        /**
         * Whether the subscription has been manually cancelled.
         */
        bool m_cancelled;

        /**
         * Weak pointer to the dispatcher for the subscription.
         */
        std::weak_ptr<EventDispatcher> m_dispatcher;

        /**
         * The name of the event that the subscription is for.
         */
        std::string m_event_name;
    };
}

#endif