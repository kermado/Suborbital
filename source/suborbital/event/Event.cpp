#include <iostream>

#include <suborbital/event/Event.hpp>

namespace suborbital
{
    Event::Event()
    {
        std::cout << "Event::Event()" << std::endl;
    }

    Event::~Event()
    {
        std::cout << "Event::~Event()" << std::endl;
    }
}