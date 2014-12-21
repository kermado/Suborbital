#include <suborbital/Entity.hpp>

namespace suborbital
{
    Entity::Entity(const std::string& name)
    : m_name(name)
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

    bool Entity::has_behaviour(const std::string& class_name) const
    {
        auto iter = m_behaviours.find(class_name);
        if (iter != m_behaviours.end()) {
            return !iter->second.empty();
        }

        return false;
    }

    Behaviour* Entity::create_behaviour(const std::string& class_name)
    {
        std::unique_ptr<Behaviour> base_behaviour = behaviour_registry().create_behaviour(class_name);
        assert(base_behaviour != nullptr);

        Behaviour* base_behaviour_ptr = base_behaviour.get();
        m_behaviours[class_name].push_back(std::move(base_behaviour));
        base_behaviour_ptr->m_entity = this;
        base_behaviour_ptr->create();

        return base_behaviour_ptr;
    }

    Behaviour* Entity::behaviour(const std::string& class_name) const
    {
        auto iter = m_behaviours.find(class_name);
        assert(iter != m_behaviours.end());
        assert(!iter->second.empty());
        return iter->second.front().get();
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