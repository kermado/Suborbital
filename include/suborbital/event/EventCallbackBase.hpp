#ifndef SUBORBITAL_EVENT_CALLBACK_BASE_HPP
#define SUBORBITAL_EVENT_CALLBACK_BASE_HPP

namespace suborbital
{
    // Forward declarations.
    class Event;

    class EventCallbackBase
    {
    public:
        virtual ~EventCallbackBase();
        virtual void operator()(std::shared_ptr<Event> event) = 0;

    protected:
        EventCallbackBase();
    };
}

#endif