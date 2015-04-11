#ifndef SUBORBITAL_COMPONENT_HPP
#define SUBORBITAL_COMPONENT_HPP

#include <suborbital/Watchable.hpp>
#include <suborbital/NonCopyable.hpp>
#include <suborbital/WatchPtr.hpp>

namespace suborbital
{
    // Forward declarations.
    class Entity;

    /**
     * The base class for components attachable to entities.
     */
    class Component : public Watchable, private NonCopyable
    {
    friend Entity;
    public:
        /**
         * Destructor.
         */
        virtual ~Component();

        /**
         * Accessor for the parent entity that the component belongs to.
         *
         * @return Pointer to the parent entity.
         */
        WatchPtr<Entity> entity() const;

    protected:
        /**
         * Constructor.
         */
        Component();

        /**
         * Called after the component has been created and attached to the entity.
         */
        virtual void create() = 0;

    private:
        /**
         * Pointer to the parent entity.
         */
        WatchPtr<Entity> m_entity;
    };
}

#endif