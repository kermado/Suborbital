#ifndef SUBORBITAL_BEHAVIOUR_HPP
#define SUBORBITAL_BEHAVIOUR_HPP

#include <suborbital/Component.hpp>

namespace suborbital
{
    // Forward declarations.
    class Entity;

    /**
     * The base class for behaviours that can be attached to entities.
     */
    class Behaviour : public Component
    {
    public:
        /**
         * Destructor.
         */
        virtual ~Behaviour();

        /**
         * Called each frame.
         *
         * @param dt Time elapsed (in seconds) since the previous call to update.
         */
        virtual void update(double dt) = 0;

    protected:
        /**
         * Constructor.
         */
        Behaviour();
    };
}

#endif