#include <iostream>

#include <suborbital/event/PythonEvent.hpp>

namespace suborbital
{
    PythonEvent::PythonEvent()
    : Event()
    , m_derived(nullptr)
    {
        std::cout << "PythonEvent::PythonEvent()" << std::endl;
    }

    PythonEvent::~PythonEvent()
    {
        std::cout << "PythonEvent::~PythonEvent()" << std::endl;
    }
}