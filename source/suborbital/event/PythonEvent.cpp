#include <iostream>

#include <suborbital/event/PythonEvent.hpp>

namespace suborbital
{
    PythonEvent::PythonEvent()
    : PythonObject()
    , Event()
    {
        std::cout << "PythonEvent::PythonEvent()" << std::endl;
    }

    PythonEvent::~PythonEvent()
    {
        std::cout << "PythonEvent::~PythonEvent()" << std::endl;
    }
}