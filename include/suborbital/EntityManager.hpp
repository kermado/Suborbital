#ifndef SUBORBITAL_ENTITY_MANAGER_HPP
#define SUBORBITAL_ENTITY_MANAGER_HPP

#include <string>
#include <set>
#include <unordered_map>

#include <suborbital/NonCopyable.hpp>
#include <suborbital/WatchPtr.hpp>
#include <suborbital/EntitySet.hpp>

namespace suborbital
{
    class Scene;
    class Entity;

    class EntityManager : private NonCopyable
    {
    friend Scene;
    public:
        /**
         * Constructor.
         *
         * @param scene Reference to the parent scene.
         */
        EntityManager(Scene& scene);

        /**
         * Destructor.
         */
        ~EntityManager();

        /**
         * Returns the set containing all of the entities in the scene.
         *
         * @return Set containing all of the entities in the scene.
         */
        const EntitySet all() const;

        /**
         * Returns the set of entities for the group specified by the provided `group_name`.
         *
         * @param group_name Name of the group.
         * @return Set containing all of the entities in the group.
         */
        const EntitySet group(const std::string& group_name) const;

        /**
         * Adds the specified `entity` to the group denoted by the provided `group_name`.
         *
         * @param group_name Name of the group to which the entity should be added.
         * @param entity Pointer to the entity that should be added to the group.
         */
        void add_to_group(const std::string& group_name, WatchPtr<Entity> entity);

        /**
         * Removes the specified `entity` from the group denoted by the provided `group_name`.
         *
         * @param group_name Name of the group from which the entity should be removed.
         * @param entity Pointer to the entity that should be removed from the group.
         */
        void remove_from_group(const std::string& group_name, WatchPtr<Entity> entity);

        /**
         * Removes the specified `entity` from all groups that it is a member of.
         *
         * @param entity Pointer to the entity that should be removed from all groups.
         */
        void remove_from_all_groups(WatchPtr<Entity> entity);

    private:
        /**
         * Creates a new entity.
         *
         * Sets the child entity's name to the empty string.
         *
         * @return Pointer to the created entity.
         */
        WatchPtr<Entity> create();

        /**
         * Creates a new entity.
         *
         * @param entity_name Unique name for the entity.
         * @return Pointer to the created entity.
         */
        WatchPtr<Entity> create(const std::string& entity_name);

        /**
         * Removes all entities that have been marked for destruction.
         *
         * This function also takes care of removing pointers to the deleted entities from any groups that the entities
         * belonged to.
         */
        void purge();

    private:
        /**
         * Reference to the parent scene.
         */
        Scene& m_scene;

        /**
         * All the entities.
         */
        EntitySet m_entities;

        /**
         * Map from group names to sets of entities.
         */
        std::unordered_map<std::string, EntitySet> m_entities_by_group;

        /**
         * Map from entities to sets of groups.
         */
        std::unordered_map<Entity*, std::set<std::string>> m_groups_by_entity;
    };
}

#endif