#include <iostream>

#include <suborbital/Entity.hpp>

#include <suborbital/scene/Scene.hpp>

namespace suborbital
{
    Scene::Scene()
    : Watchable()
    , m_entities(*this)
    , m_camera(nullptr)
    , m_systems()
    {
        std::cout << "Scene::Scene()" << std::endl;
    }

    Scene::~Scene()
    {
        std::cout << "Scene::~Scene()" << std::endl;
    }

    EntityManager& Scene::entities()
    {
        return m_entities;
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
        return m_entities.create();
    }

    WatchPtr<Entity> Scene::create_entity(const std::string& entity_name)
    {
        return m_entities.create(entity_name);
    }

    void Scene::broadcast(const std::string& event_name, std::shared_ptr<suborbital::Event> event)
    {
        const EntitySet& entities = m_entities.all();
        for (auto iter = entities.cbegin(); iter != entities.cend(); ++iter)
        {
            const WatchPtr<Entity>& entity = *iter;
            entity->broadcast(event_name, event);
        }
    }

    WatchPtr<System> Scene::system(const std::string& name)
    {
        auto iter = m_systems.find(name);
        if (iter != m_systems.end())
        {
            std::unique_ptr<System>& system = iter->second;
            return WatchPtr<System>(system.get());
        }

        return nullptr;
    }

    void Scene::process(double dt)
    {
        // 1. Call the scene's update function.
        update(dt);

        // 2. Process all of the systems.
        for (const auto& kv : m_systems)
        {
            kv.second->process(dt);
        }

        // 3. Update all of the alive entities in the scene.
        const EntitySet& entities = m_entities.all();
        for (auto iter = entities.cbegin(); iter != entities.cend(); ++iter)
        {
            const WatchPtr<Entity>& entity = *iter;
            if (entity->alive())
            {
                entity->update(dt);
            }
        }

        // 4. Delete all the entities marked for destruction.
        m_entities.purge();
    }
}