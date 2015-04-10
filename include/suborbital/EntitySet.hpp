#ifndef SUBORBITAL_ENTITY_GROUP_HPP
#define SUBORBITAL_ENTITY_GROUP_HPP

#include <set>

#include <suborbital/NonCopyable.hpp>
#include <suborbital/WatchPtr.hpp>

namespace suborbital
{
    // Forward declarations.
    class Entity;

    class EntitySet : private NonCopyable
    {
    public:
        /**
         * Iterator to an entity in the group.
         */
        typedef std::set<WatchPtr<Entity>>::iterator iterator;

        /**
         * Iterator to a const entity in the group.
         */
        typedef std::set<WatchPtr<Entity>>::const_iterator const_iterator;

    public:
        /**
         * Constructor.
         */
        EntitySet();

        /**
         * Destructor.
         */
        ~EntitySet();

        /**
         * Copy constructor.
         *
         * @param other The other EntitySet to copy from.
         */
        EntitySet(const EntitySet& other);

        /**
         * Copy assignment operator.
         *
         * @param other The other EntitySet to copy from.
         */
        EntitySet& operator=(const EntitySet& other);

        /**
         * Accessor for the number of entities in the group.
         *
         * @return The number of entities in the group.
         */
        std::size_t size() const;

        /**
         * Checks whether the group is empty (i.e. whether its `size` is zero).
         *
         * @return True if the group contains no entities, false otherwise.
         */
        bool empty() const;

        /**
         * Searches the group for the specified entity and returns an iterator to it if found, otherwise returns an
         * iterator to `end`.
         *
         * This function has time complexity logarithmic in the size of the group, O(log n).
         *
         * @return Iterator to the specified entity in the group or `end` if the entity was not found.
         */
        iterator find(WatchPtr<Entity> entity);

        /**
         * Searches the group for the specified entity and returns an iterator to it if found, otherwise returns an
         * iterator to `end`.
         *
         * This function has time complexity logarithmic in the size of the group, O(log n).
         *
         * @return Iterator to the specified entity in the group or `end` if the entity was not found.
         */
        const_iterator find(WatchPtr<Entity> entity) const;

        /**
         * Searches for an entity with the specified `name` and returns an iterator to it if found, otherwise returns
         * an iterator to `end`.
         *
         * Note that this function performs a linear search and has time complexity logarithmic in the size of the
         * group, O(n). Avoid calling this function every frame and cache the result where possible.
         *
         * @param entity_name Name of the entity to search for.
         * @return Iterator to the first entity found having the specified `name`.
         */
        iterator find_by_name(const std::string& entity_name);

        /**
         * Searches for an entity with the specified `name` and returns an iterator to it if found, otherwise returns
         * an iterator to `end`.
         *
         * Note that this function performs a linear search and has time complexity logarithmic in the size of the
         * group, O(n). Avoid calling this function every frame and cache the result where possible.
         *
         * @param entity_name Name of the entity to search for.
         * @return Iterator to the first entity found having the specified `name`.
         */
        const_iterator find_by_name(const std::string& entity_name) const;

        /**
         * Inserts the supplied entity into the group.
         *
         * @param entity Entity to be added into the group.
         * @return Iterator to the inserted entity.
         */
        iterator insert(WatchPtr<Entity> entity);

        /**
         * Removes the entity at the specified `position` from the group.
         *
         * @param position Iterator to the entity to remove from the group.
         * @return Iterator to the next entity in the group.
         */
        iterator remove(const_iterator position);

        /**
         * Finds and removes the specified entity from the group.
         *
         * This function has time complexity logarithmic in the size of the group, O(log n).
         *
         * @param entity Pointer to the entity to remove from the group.
         * @return True if the specified entity was found and removed, false otherwise.
         */
        bool remove(WatchPtr<Entity> entity);

        /**
         * Removes all entities from the group.
         */
        void clear();

        /**
         * Returns an iterator referring to the first entity in the group.
         *
         * @return Iterator to the first entity in the group.
         */
        iterator begin();

        /**
         * Returns an iterator referring to the first entity in the group.
         *
         * @return Iterator to the first entity in the group.
         */
        const_iterator cbegin() const;

        /**
         * Returns an iterator referring to the past-the-end entity in the group.
         *
         * The past-the-end entity is a theoretical entity that would follow the last entity in the group.
         *
         * @return Iterator to the past-the-end entity in the group.
         */
        iterator end();

        /**
         * Returns an iterator referring to the past-the-end entity in the group.
         *
         * The past-the-end entity is a theoretical entity that would follow the last entity in the group.
         *
         * @return Iterator to the past-the-end entity in the group.
         */
        const_iterator cend() const;

    private:
        /**
         * Entities in the group.
         */
        std::set<WatchPtr<Entity>> m_entities;
    };
}

#endif