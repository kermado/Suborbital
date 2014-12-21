#include <iostream>
#include <cassert>

#include <suborbital/Component.hpp>

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

    Entity* Component::entity() const
    {
        assert(m_entity != nullptr);
        return m_entity;
    }
}