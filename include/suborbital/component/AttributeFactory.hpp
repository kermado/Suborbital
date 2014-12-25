#ifndef SUBORBITAL_ATTRIBUTE_FACTORY_HPP
#define SUBORBITAL_ATTRIBUTE_FACTORY_HPP

#include <iostream>

#include <suborbital/component/ComponentFactory.hpp>
#include <suborbital/component/Attribute.hpp>

namespace suborbital
{
    /**
     * Factory class for attributes.
     *
     * This class is used internally for instantiating attributes.
     */
    template<typename AttributeType>
    class AttributeFactory : public ComponentFactory
    {
    public:
        /**
         * Constructor.
         */
        AttributeFactory() = default;

        /**
         * Destructor.
         */
        ~AttributeFactory() = default;

        /**
         * Instantiates an attribute of the provided type and returns a unique_ptr to the created attribute.
         *
         * @note The caller is responsible for managing the lifetime of the returned attribute.
         *
         * @return Unique pointer to the created attribute.
         */
        std::unique_ptr<Component> create() const
        {
            static_assert(std::is_base_of<Attribute, AttributeType>::value,
                    "Template parameter AttributeType in AttributeFactory is not derived from Attribute");
            return std::unique_ptr<AttributeType>(new AttributeType());
        }
    };
}

#endif