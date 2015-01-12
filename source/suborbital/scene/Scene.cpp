#include <iostream>

#include <suborbital/Entity.hpp>
#include <suborbital/scene/Scene.hpp>

namespace suborbital
{
    Scene::Scene()
    : Watchable()
    , m_entities()
    , m_camera(nullptr)
    {
        std::cout << "Scene::Scene()" << std::endl;
    }

    Scene::~Scene()
    {
        std::cout << "Scene::~Scene()" << std::endl;
    }

    bool Scene::has_camera() const
    {
        return static_cast<bool>(m_camera);
    }

    WatchPtr<Entity> Scene::camera() const
    {
        return m_camera;
    }

    void Scene::camera(WatchPtr<Entity> camera_entity)
    {
        m_camera = camera_entity;
    }

    WatchPtr<Entity> Scene::create_entity()
    {
        Entity* entity = new Entity(*this);
        m_entities.push_back(std::unique_ptr<Entity>(entity));
        return WatchPtr<Entity>(entity);
    }

    WatchPtr<Entity> Scene::create_entity(const std::string& name)
    {
        Entity* entity = new Entity(*this, name);
        m_entities.push_back(std::unique_ptr<Entity>(entity));
        return WatchPtr<Entity>(entity);
    }

    WatchPtr<Entity> Scene::find(const std::string& name) const
    {
        for (const std::unique_ptr<Entity>& entity : m_entities)
        {
            if (entity->name() == name)
            {
                return WatchPtr<Entity>(entity.get());
            }
        }

        return nullptr;
    }

    void Scene::broadcast(const std::string& event_name, std::shared_ptr<suborbital::Event> event)
    {
        for (std::unique_ptr<Entity>& entity : m_entities)
        {
            entity->broadcast(event_name, event);
        }
    }

    void Scene::process(double dt)
    {
        update(dt);

        for (std::unique_ptr<Entity>& entity : m_entities)
        {
            entity->update(dt);
        }
    }
}