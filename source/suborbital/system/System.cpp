#include <cassert>

#include <suborbital/system/System.hpp>

namespace suborbital
{
    System::System()
    : m_scene(nullptr)
    {
        // Nothing to do.
    }

    System::~System()
    {
        // Nothing to do.
    }

    WatchPtr<Scene> System::scene() const
    {
        return m_scene;
    }
}