#ifndef SUBORBITAL_ATTRIBUTE_FACTORY_HPP
#define SUBORBITAL_ATTRIBUTE_FACTORY_HPP

#include <iostream>

#include <suborbital/component/ComponentFactory.hpp>
#include <suborbital/component/Attribute.hpp>

namespace suborbital
{
    template<typename AttributeType>
    class AttributeFactory : public ComponentFactory
    {
    public:
        AttributeFactory() = default;
        ~AttributeFactory() = default;

        std::unique_ptr<Component> create() const
        {
            static_assert(std::is_base_of<Attribute, AttributeType>::value,
                    "Template parameter AttributeType in AttributeFactory is not derived from Attribute");
            return std::unique_ptr<AttributeType>(new AttributeType());
        }
    };
}

#endif