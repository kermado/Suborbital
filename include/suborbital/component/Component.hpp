#ifndef SUBORBITAL_COMPONENT_HPP
#define SUBORBITAL_COMPONENT_HPP

#include <suborbital/Watchable.hpp>
#include <suborbital/NonCopyable.hpp>

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
         * Called after the component has been created and assigned to the entity.
         */
        virtual void create() = 0;

        /**
         * Accessor for the parent entity that the component belongs to.
         *
         * @note The component lifetime is tied to its parent entity.
         *
         * @return Pointer to the parent entity.
         */
        Entity* entity() const;

    protected:
        /**
         * Constructor.
         */
        Component();

    private:
        /**
         * Pointer to the parent entity.
         * Note that the component's lifetime is tied to its parent entity.
         */
        Entity* m_entity;
    };
}

#endif