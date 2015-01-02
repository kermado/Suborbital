#include <suborbital/Entity.hpp>
#include <suborbital/event/EventCallbackBase.hpp>
#include <suborbital/event/EventSubscription.hpp>

namespace suborbital
{
    Entity::Entity()
    : m_name()
    , m_event_dispatcher(new EventDispatcher())
    , m_attributes()
    , m_behaviours()
    {
        std::cout << "Entity::Entity()" << std::endl;
    }

    Entity::Entity(const std::string& name)
    : m_name(name)
    , m_event_dispatcher(new EventDispatcher())
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

    watch_ptr<Attribute> Entity::create_attribute(const std::string& class_name)
    {
        std::unique_ptr<Attribute> attribute = component_registry().create_attribute(class_name);
        assert(attribute != nullptr);

        Attribute* attribute_ptr = attribute.get();
        m_attributes[class_name].push_back(std::move(attribute));
        attribute_ptr->m_entity = this;
        attribute_ptr->create();

        return watch_ptr<Attribute>(attribute_ptr);
    }

    watch_ptr<Attribute> Entity::attribute(const std::string& class_name) const
    {
        auto iter = m_attributes.find(class_name);
        assert(iter != m_attributes.end());
        assert(iter->second.empty() == false);

        Attribute* attribute = iter->second.front().get();
        watch_ptr<Attribute> watch_attribute(attribute);
        return watch_attribute;
    }

    void Entity::create_behaviour(const std::string& class_name)
    {
        std::unique_ptr<Behaviour> behaviour = component_registry().create_behaviour(class_name);
        assert(behaviour != nullptr);

        Behaviour* behaviour_ptr = behaviour.get();
        m_behaviours[class_name].push_back(std::move(behaviour));
        behaviour_ptr->m_entity = this;
        behaviour_ptr->create();
    }

    void Entity::publish(const std::string& event_name, std::shared_ptr<Event> event)
    {
        m_event_dispatcher->publish(event_name, event);
    }

    std::unique_ptr<EventSubscription> Entity::subscribe(const std::string& event_name,
            std::unique_ptr<EventCallbackBase> callback)
    {
        return m_event_dispatcher->subscribe(event_name, std::move(callback));
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