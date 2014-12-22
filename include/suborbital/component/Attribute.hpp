#ifndef SUBORBITAL_ATTRIBUTE_HPP
#define SUBORBITAL_ATTRIBUTE_HPP

#include <suborbital/component/Component.hpp>

namespace suborbital
{
    /**
     * The base class for attributes that can be attached to entities.
     */
    class Attribute : public Component
    {
    public:
        /**
         * Destructor.
         */
        virtual ~Attribute();

    protected:
        /**
         * Constructor.
         */
        Attribute();
    };
}

#endif