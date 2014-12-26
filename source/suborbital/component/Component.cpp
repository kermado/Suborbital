#include <iostream>

#include <suborbital/component/Component.hpp>

namespace suborbital
{
    Component::Component()
    : m_entity(nullptr)
    {
        std::cout << "Component::Component()" << std::endl;
    }

    Component::~Component()
    {
        std::cout << "Component::~Component()" << std::endl;
    }

    watch_ptr<Entity> Component::entity() const
    {
        return m_entity;
    }
}