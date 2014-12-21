#include <cassert>
#include <iostream>

#include <suborbital/Behaviour.hpp>

namespace suborbital
{
    Behaviour::Behaviour()
    : Component()
    {
        std::cout << "Behaviour::Behaviour()" << std::endl;
    }

    Behaviour::~Behaviour()
    {
        std::cout << "Behaviour::~Behaviour()" << std::endl;
    }
}