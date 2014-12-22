#ifndef SUBORBITAL_COMPONENT_FACTORY_HPP
#define SUBORBITAL_COMPONENT_FACTORY_HPP

#include <memory>

namespace suborbital
{
    class Component;

    class ComponentFactory
    {
    public:
        ComponentFactory() = default;
        virtual ~ComponentFactory() = default;
        virtual std::unique_ptr<Component> create() const = 0;
    };
}

#endif