#ifndef SUBORBITAL_ENTITY_GROUP_HPP
#define SUBORBITAL_ENTITY_GROUP_HPP

#include <set>

#include <suborbital/WatchPtr.hpp>

namespace suborbital
{
    // Forward declarations.
    class Entity;

    /**
     * Represents a set of entities.
     *
     * No duplicates of an entity may exist in the set.
     */
    class EntitySet
    {
    public:
        /**
         * Iterator to an entity in the set.
         */
        typedef std::set<WatchPtr<Entity>>::iterator iterator;

        /**
         * Iterator to a const entity in the set.
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
         * Accessor for the number of entities in the set.
         *
         * @return The number of entities in the set.
         */
        std::size_t size() const;

        /**
         * Checks whether the set is empty (i.e. whether its `size` is zero).
         *
         * @return True if the set contains no entities, false otherwise.
         */
        bool empty() const;

        /**
         * Searches the set for the specified entity and returns an iterator to it if found, otherwise returns an
         * iterator to `end`.
         *
         * This function has time complexity logarithmic in the size of the set, O(1og n).
         *
         * @return Iterator to the specified entity in the set or `end` if the entity was not found.
         */
        iterator find(WatchPtr<Entity> entity);

        /**
         * Searches the set for the specified entity and returns an iterator to it if found, otherwise returns an
         * iterator to `end`.
         *
         * This function has time complexity logarithmic in the size of the set, O(1og n).
         *
         * @return Iterator to the specified entity in the set or `end` if the entity was not found.
         */
        const_iterator find(WatchPtr<Entity> entity) const;

        /**
         * Searches for an entity with the specified `name` and returns an iterator to it if found, otherwise returns
         * an iterator to `end`.
         *
         * Note that this function performs a linear search and has time complexity logarithmic in the size of the set,
         * O(n). Avoid calling this function every frame and cache the result where possible.
         *
         * @param entity_name Name of the entity to search for.
         * @return Iterator to the first entity found having the specified `name`.
         */
        iterator find_by_name(const std::string& entity_name);

        /**
         * Searches for an entity with the specified `name` and returns an iterator to it if found, otherwise returns
         * an iterator to `end`.
         *
         * Note that this function performs a linear search and has time complexity logarithmic in the size of the set,
         * O(n). Avoid calling this function every frame and cache the result where possible.
         *
         * @param entity_name Name of the entity to search for.
         * @return Iterator to the first entity found having the specified `name`.
         */
        const_iterator find_by_name(const std::string& entity_name) const;

        /**
         * Inserts the supplied entity into the set.
         *
         * This function has time complexity logarithmic in the size of the set, O(1og n).
         *
         * @param entity Entity to be added into the set.
         * @return Iterator to the inserted entity.
         */
        iterator insert(WatchPtr<Entity> entity);

        /**
         * Removes the entity at the specified `position` from the set.
         *
         * This function has time complexity logarithmic in the size of the set, O(1og n).
         *
         * @param position Iterator to the entity to remove from the set.
         * @return Iterator to the next entity in the set.
         */
        iterator remove(const_iterator position);

        /**
         * Finds and removes the specified entity from the set.
         *
         * This function has time complexity logarithmic in the size of the set, O(1og n).
         *
         * @param entity Pointer to the entity to remove from the set.
         * @return True if the specified entity was found and removed, false otherwise.
         */
        bool remove(WatchPtr<Entity> entity);

        /**
         * Removes all entities from the set.
         */
        void clear();

        /**
         * Returns an iterator referring to the first entity in the set.
         *
         * @return Iterator to the first entity in the set.
         */
        iterator begin();

        /**
         * Returns an iterator referring to the first entity in the set.
         *
         * @return Iterator to the first entity in the set.
         */
        const_iterator cbegin() const;

        /**
         * Returns an iterator referring to the past-the-end entity in the set.
         *
         * The past-the-end entity is a theoretical entity that would follow the last entity in the set.
         *
         * @return Iterator to the past-the-end entity in the set.
         */
        iterator end();

        /**
         * Returns an iterator referring to the past-the-end entity in the set.
         *
         * The past-the-end entity is a theoretical entity that would follow the last entity in the set.
         *
         * @return Iterator to the past-the-end entity in the set.
         */
        const_iterator cend() const;

    private:
        /**
         * Entities in the set.
         *
         * TODO: Change implementation to use std::unordered_set when this is supported by SWIG.
         */
        std::set<WatchPtr<Entity>> m_entities;
    };
}

#endif