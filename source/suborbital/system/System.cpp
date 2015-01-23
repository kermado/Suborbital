#include <iostream>
#include <cassert>

#include <suborbital/system/System.hpp>

namespace suborbital
{
    System::System()
    : m_scene(nullptr)
    {
        std::cout << "System::System()" << std::endl;
    }

    System::~System()
    {
        std::cout << "System::~System()" << std::endl;
    }

    WatchPtr<Scene> System::scene() const
    {
        return m_scene;
    }
}