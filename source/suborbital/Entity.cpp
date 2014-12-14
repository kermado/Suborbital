#include <iostream>

#include <suborbital/Entity.hpp>
#include <suborbital/component/Component.hpp>

namespace suborbital
{
    Entity::Entity(const std::string& name)
    : m_name(name)
    , m_components()
    {
        std::cout << "Entity::Entity(" << name << ")" << std::endl;
    }

    Entity::~Entity()
    {
        std::cout << "Entity::~Entity(" << m_name << ")" << std::endl;
    }

    const std::string& Entity::name() const
    {
        return m_name;
    }

    bool Entity::has_component(const std::string& class_name) const
    {
        auto iter = m_components.find(class_name);
        if (iter != m_components.end()) {
            return !iter->second.empty();
        }

        return false;
    }

    component::Component* Entity::create_component(const std::string& class_name)
    {
        std::unique_ptr<component::Component> base_component = component::create(class_name);
        component::Component* base_component_ptr = base_component.get();
        m_components[class_name].push_back(std::move(base_component));
        base_component_ptr->m_entity = this;
        base_component_ptr->create();
        return base_component_ptr;
    }

    component::Component* Entity::component(const std::string& class_name) const
    {
        auto iter = m_components.find(class_name);
        assert(iter != m_components.end());
        assert(!iter->second.empty());
        return iter->second.front().get();
    }

    void Entity::update(double dt)
    {
        for (auto iter = m_components.begin(); iter != m_components.end(); ++iter)
        {
            for (auto& c : iter->second)
            {
                c->update(dt);
            }
        }
    }
}