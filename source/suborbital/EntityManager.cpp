#include <cassert>

#include <suborbital/Entity.hpp>
#include <suborbital/EntityManager.hpp>

#include <suborbital/scene/Scene.hpp>

namespace suborbital
{
    EntityManager::EntityManager(Scene& scene)
    : m_scene(scene)
    , m_entities()
    , m_entities_by_group()
    , m_groups_by_entity()
    , m_empty_set()
    {
        // Nothing to do.
    }

    EntityManager::~EntityManager()
    {
        for (auto iter = m_entities.begin(); iter != m_entities.end(); ++iter)
        {
            const WatchPtr<Entity>& entity = *iter;
            assert(static_cast<bool>(entity) == true);

            delete entity.get();
        }
    }

    const EntitySet& EntityManager::all() const
    {
        return m_entities;
    }

    const EntitySet& EntityManager::group(const std::string& group_name) const
    {
        auto position = m_entities_by_group.find(group_name);
        if (position != m_entities_by_group.end())
        {
            return position->second;
        }

        return m_empty_set;
    }

    void EntityManager::add_to_group(const std::string& group_name, WatchPtr<Entity> entity)
    {
        EntitySet& group = m_entities_by_group[group_name];
        assert(group.find(entity) == group.end());

        group.insert(entity);
        m_groups_by_entity[entity.get()].insert(group_name);
    }

    void EntityManager::remove_from_group(const std::string& group_name, WatchPtr<Entity> entity)
    {
        EntitySet& group = m_entities_by_group[group_name];
        bool success = group.remove(entity);

        assert(success == true);
    }

    void EntityManager::remove_from_all_groups(WatchPtr<Entity> entity)
    {
        // Remove the entity from any groups that it is a member of.
        for (const std::string& group_name : m_groups_by_entity[entity.get()])
        {
            remove_from_group(group_name, entity);
        }

        // Remove the set of group names that the entity is a member of.
        std::size_t removals = m_groups_by_entity.erase(entity.get());
        assert(removals == 1);
    }

    WatchPtr<Entity> EntityManager::create()
    {
        Entity* entity = new Entity(m_scene);
        auto position = m_entities.insert(WatchPtr<Entity>(entity));
        return *position;
    }

    WatchPtr<Entity> EntityManager::create(const std::string& entity_name)
    {
        Entity* entity = new Entity(m_scene, entity_name);
        auto position = m_entities.insert(WatchPtr<Entity>(entity));
        return *position;
    }

    void EntityManager::purge()
    {
        for (auto iter = m_entities.begin(); iter != m_entities.end();)
        {
            const WatchPtr<Entity>& entity = *iter;
            if (entity->dead())
            {
                // Remove the entity from all of the groups that it is a member of.
                remove_from_all_groups(entity);

                // Remove the entity from the set of all entities and update the iterator to point to the next entity.
                iter = m_entities.remove(iter);

                // Delete the entity
                delete entity.get();
            }
            else
            {
                // Move onto the next entity in the set.
                ++iter;
            }
        }
    }
}