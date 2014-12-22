#include <suborbital/Entity.hpp>

namespace suborbital
{
    Entity::Entity(const std::string& name)
    : m_name(name)
    , m_attributes()
    , m_behaviours()
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

    bool Entity::has_attribute(const std::string& class_name) const
    {
        auto iter = m_attributes.find(class_name);
        if (iter != m_attributes.end())
        {
            return !iter->second.empty();
        }

        return false;
    }

    suborbital::Attribute* Entity::create_attribute(const std::string& class_name)
    {
        std::unique_ptr<Attribute> attribute = component_registry().create_attribute(class_name);
        assert(attribute != nullptr);

        Attribute* attribute_ptr = attribute.get();
        m_attributes[class_name].push_back(std::move(attribute));
        attribute_ptr->m_entity = this;
        attribute_ptr->create();

        return attribute_ptr;
    }

    Attribute* Entity::attribute(const std::string& class_name) const
    {
        auto iter = m_attributes.find(class_name);
        assert(iter != m_attributes.end());
        assert(!iter->second.empty());
        return iter->second.front().get();
    }

    Behaviour* Entity::create_behaviour(const std::string& class_name)
    {
        std::unique_ptr<Behaviour> behaviour = component_registry().create_behaviour(class_name);
        assert(behaviour != nullptr);

        Behaviour* behaviour_ptr = behaviour.get();
        m_behaviours[class_name].push_back(std::move(behaviour));
        behaviour_ptr->m_entity = this;
        behaviour_ptr->create();

        return behaviour_ptr;
    }

    void Entity::update(double dt)
    {
        for (auto iter = m_behaviours.begin(); iter != m_behaviours.end(); ++iter)
        {
            for (auto& c : iter->second)
            {
                c->update(dt);
            }
        }
    }
}