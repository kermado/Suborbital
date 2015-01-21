#include <iostream>
#include <cassert>

#include <suborbital/system/System.hpp>

namespace suborbital
{
    System::System(Scene& scene)
    : m_scene(scene)
    {
        std::cout << "System::System()" << std::endl;
    }

    System::~System()
    {
        std::cout << "System::~System()" << std::endl;
    }
}