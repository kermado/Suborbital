#include <iostream>

#include <suborbital/event/EventCallbackBase.hpp>

namespace suborbital
{
    EventCallbackBase::EventCallbackBase()
    {
        std::cout << "EventCallbackBase::EventCallbackBase()" << std::endl;
    }

    EventCallbackBase::~EventCallbackBase()
    {
        std::cout << "EventCallbackBase::~EventCallbackBase()" << std::endl;
    }
}