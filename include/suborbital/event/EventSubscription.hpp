#ifndef SUBORBITAL_EVENT_SUBSCRIPTION_HPP
#define SUBORBITAL_EVENT_SUBSCRIPTION_HPP

#include <string>

#include <suborbital/NonCopyable.hpp>
#include <suborbital/watch_ptr.hpp>

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
        EventSubscription(watch_ptr<EventDispatcher> dispatcher, const std::string& event_name, std::size_t callback_index);

    private:
        /**
         * Whether the subscription has been manually cancelled.
         */
        bool m_cancelled;

        /**
         * The dispatcher for the subscription.
         */
        watch_ptr<EventDispatcher> m_dispatcher;

        /**
         * The name of the event that the subscription is for.
         */
        std::string m_event_name;

        /**
         * The index into the list of event callbacks for the subscription's callback function.
         */
        std::size_t m_callback_index;
    };
}

#endif