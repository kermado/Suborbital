#ifndef SUBORBITAL_COMPONENT_FACTORY_HPP
#define SUBORBITAL_COMPONENT_FACTORY_HPP

#include <memory>

namespace suborbital
{
    // Forward declarations.
    class Component;

    /**
     * The base class for factories that instantiate components.
     */
    class ComponentFactory
    {
    public:
        /**
         * Constructor.
         */
        ComponentFactory() = default;

        /**
         * Destructor.
         */
        virtual ~ComponentFactory() = default;

        /**
         * Instantiates a component and returns a unique_ptr to the created component.
         *
         * @note The caller is responsible for managing the lifetime of the returned component.
         *
         * @return Unique pointer to the created component.
         */
        virtual std::unique_ptr<Component> create() const = 0;
    };
}

#endif