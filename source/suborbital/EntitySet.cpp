#include <suborbital/Entity.hpp>
#include <suborbital/EntitySet.hpp>

namespace suborbital
{
    EntitySet::EntitySet()
    : m_entities()
    {
        // Nothing to do.
    }

    EntitySet::~EntitySet()
    {
        // Nothing to do.
    }

    std::size_t EntitySet::size() const
    {
        return m_entities.size();
    }

    bool EntitySet::empty() const
    {
        return m_entities.empty();
    }

    EntitySet::iterator EntitySet::find(WatchPtr<Entity> entity)
    {
        return m_entities.find(entity);
    }

    EntitySet::const_iterator EntitySet::find(WatchPtr<Entity> entity) const
    {
        return m_entities.find(entity);
    }

    EntitySet::iterator EntitySet::find_by_name(const std::string& entity_name)
    {
        for (auto iter = m_entities.begin(); iter != m_entities.end(); ++iter)
        {
            const WatchPtr<Entity>& entity = *iter;
            if (entity->name() == entity_name)
            {
                return iter;
            }
        }

        return end();
    }

    EntitySet::const_iterator EntitySet::find_by_name(const std::string& entity_name) const
    {
        for (auto iter = m_entities.begin(); iter != m_entities.end(); ++iter)
        {
            const WatchPtr<Entity>& entity = *iter;
            if (entity->name() == entity_name)
            {
                return iter;
            }
        }

        return cend();
    }

    EntitySet::iterator EntitySet::insert(WatchPtr<Entity> entity)
    {
        std::pair<iterator, bool> insertion = m_entities.insert(entity);
        return insertion.first;
    }

    EntitySet::iterator EntitySet::remove(const_iterator position)
    {
        return m_entities.erase(position);
    }

    bool EntitySet::remove(WatchPtr<Entity> entity)
    {
        auto position = m_entities.find(entity);
        if (position != m_entities.end())
        {
            m_entities.erase(position);
            return true;
        }

        return false;
    }

    void EntitySet::clear()
    {
        m_entities.clear();
    }

    EntitySet::iterator EntitySet::begin()
    {
        return m_entities.begin();
    }

    EntitySet::const_iterator EntitySet::cbegin() const
    {
        return m_entities.cbegin();
    }

    EntitySet::iterator EntitySet::end()
    {
        return m_entities.end();
    }

    EntitySet::const_iterator EntitySet::cend() const
    {
        return m_entities.cend();
    }
}