#include <suborbital/Entity.hpp>

#include <suborbital/scene/Scene.hpp>

#include <suborbital/event/EventCallbackBase.hpp>
#include <suborbital/event/EventSubscription.hpp>

#include <suborbital/system/System.hpp>

namespace suborbital
{
    Entity::Entity(Scene& scene)
    : Watchable()
    , m_scene(scene)
    , m_name()
    , m_dead(false)
    , m_parent(nullptr)
    , m_children()
    , m_event_dispatcher(new EventDispatcher())
    , m_attributes()
    , m_behaviours()
    {
        std::cout << "Entity::Entity()" << std::endl;
    }

    Entity::Entity(Scene& scene, const std::string& name)
    : Watchable()
    , m_scene(scene)
    , m_name(name)
    , m_parent(nullptr)
    , m_children()
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

    Scene& Entity::scene() const
    {
        return m_scene;
    }

    const std::string& Entity::name() const
    {
        return m_name;
    }

    bool Entity::dead() const
    {
        return m_dead;
    }

    bool Entity::alive() const
    {
        return !m_dead;
    }

    void Entity::destroy()
    {
        assert(m_dead == false);
        m_dead = true;
    }

    void Entity::add_to_group(const std::string& group_name)
    {
        m_scene.entities().add_to_group(group_name, WatchPtr<Entity>(this));
    }

    void Entity::remove_from_group(const std::string& group_name)
    {
        m_scene.entities().remove_from_group(group_name, WatchPtr<Entity>(this));
    }

    bool Entity::has_children() const
    {
        return m_children.empty() == false;
    }

    bool Entity::has_parent() const
    {
        return static_cast<bool>(m_parent);
    }

    WatchPtr<Entity> Entity::create_child()
    {
        Entity* child = new Entity(m_scene);
        child->m_parent = WatchPtr<Entity>(this);
        m_children.push_back(std::unique_ptr<Entity>(child));
        return WatchPtr<Entity>(child);
    }

    WatchPtr<Entity> Entity::create_child(const std::string& name)
    {
        Entity* child = new Entity(m_scene, name);
        child->m_parent = WatchPtr<Entity>(this);
        m_children.push_back(std::unique_ptr<Entity>(child));
        return WatchPtr<Entity>(child);
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

    WatchPtr<Attribute> Entity::create_attribute(const std::string& class_name)
    {
        std::unique_ptr<Attribute> attribute = component_registry().create_attribute(class_name);
        assert(attribute != nullptr);

        Attribute* attribute_ptr = attribute.get();
        m_attributes[class_name].push_back(std::move(attribute));
        attribute_ptr->m_entity = this;
        attribute_ptr->create();

        return WatchPtr<Attribute>(attribute_ptr);
    }

    WatchPtr<Attribute> Entity::attribute(const std::string& class_name) const
    {
        auto iter = m_attributes.find(class_name);
        assert(iter != m_attributes.end());
        assert(iter->second.empty() == false);

        Attribute* attribute = iter->second.front().get();
        WatchPtr<Attribute> watch_attribute(attribute);
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

    void Entity::broadcast_descendents(const std::string& event_name, std::shared_ptr<suborbital::Event> event)
    {
        for (auto& child : m_children)
        {
            child->broadcast(event_name, event);
        }
    }

    void Entity::broadcast(const std::string& event_name, std::shared_ptr<suborbital::Event> event)
    {
        publish(event_name, event);

        for (auto& child : m_children)
        {
            child->broadcast(event_name, event);
        }
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