#include <suborbital/component/Component.hpp>

namespace suborbital
{
    Component::Component()
    : m_entity(nullptr)
    {
        // Nothing to do.
    }

    Component::~Component()
    {
        // Nothing to do.
    }

    WatchPtr<Entity> Component::entity() const
    {
        return m_entity;
    }
}