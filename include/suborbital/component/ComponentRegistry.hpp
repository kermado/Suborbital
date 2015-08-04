#ifndef SUBORBITAL_COMPONENT_REGISTRY_HPP
#define SUBORBITAL_COMPONENT_REGISTRY_HPP

#include <string>
#include <memory>
#include <cassert>
#include <unordered_map>
#include <typeindex>

#include <suborbital/NonCopyable.hpp>
#include "ComponentFactory.hpp"

/**
 * Macro for associating a string name to a c++ type.
 *
 * @param T Type to be associated with a string of the same name.
 */
#define TYPE(T)                                                                                                        \
namespace suborbital                                                                                                   \
{                                                                                                                      \
    template<>                                                                                                         \
    struct Type<T>                                                                                                     \
    {                                                                                                                  \
        static std::string name()                                                                                      \
        {                                                                                                              \
            return #T;                                                                                                 \
        }                                                                                                              \
    };                                                                                                                 \
}                                                                                                                      \

namespace suborbital
{
    // Forward declarations.
    class Component;
    class ComponentFactory;
    class Attribute;
    class Behaviour;

    /**
     * Type naming system used for associating string names to c++ types.
     *
     * The `TYPE` macro will generate a specialisation of the `TypeName` template class for the provided type.
     * Note that this is done automatically when using the `REGISTER_ATTRIBUTE` and `REGISTER_BEHAVIOUR` macros.
     */
    template <typename T>
    struct Type
    {
        static std::string name()
        {
            assert(0); // Specialisation for `T` has not been provided.
        }
    };

    /**
     * Component registry.
     */
    class ComponentRegistry : public NonCopyable
    {
    private:
        /**
         * Component factories registry type definition.
         */
        typedef std::unordered_map<std::string, std::unique_ptr<ComponentFactory>> FactoryRegistry;

    public:
        /**
         * Constructor.
         */
        ComponentRegistry();

        /**
         * Destructor.
         */
        ~ComponentRegistry();

        /**
         * Registers the provided component type to the specified factory.
         *
         * @param factory Factory to use for instantiating components of the provided `ComponentType`.
         */
        template<typename ComponentType>
        void register_component(std::unique_ptr<ComponentFactory> factory)
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "Template parameter ComponentType in"
                    " ComponentRegistry::register_component is not derived from Component");

            m_factory_registry.insert(FactoryRegistry::value_type(Type<ComponentType>::name(), std::move(factory)));
        }

        /**
         * Registers the supplied component factory function to the specified name.
         *
         * @note This method does not register the specified component name to a specific c++ type. This function is
         * used for registering scripted components.
         *
         * @param name Name to associate with the provided component factory function.
         * @param factory Factory to use for instantiating components of the specified name.
         */
        void register_component(const std::string& name, std::unique_ptr<ComponentFactory> factory);

        /**
         * Creates and returns an instance of the attribute registered to the provided attribute name.
         *
         * @param name Name of the attribute for which to create.
         * @return Instance of the attribute associated with the specified attribute name.
         */
        std::unique_ptr<Attribute> create_attribute(const std::string& name) const;

        /**
         * Creates and returns an instance of the attribute registered to the provided attribute type.
         *
         * @return Instance of the attribute associated with the provided attribute type.
         */
        template<typename AttributeType>
        std::unique_ptr<AttributeType> create_attribute() const
        {
            static_assert(std::is_base_of<Attribute, AttributeType>::value, "Template parameter AttributeType in"
                    " ComponentRegistry::create_attribute is not derived from Attribute");

            return std::dynamic_pointer_cast<std::unique_ptr<AttributeType>>(create_attribute(Type<AttributeType>::name()));
        }

        /**
         * Creates and returns an instance of the behaviour registered to the provided behaviour name.
         *
         * @param name Name of the behaviour for which to create.
         * @return Instance of the behaviour associated with the specified behaviour name.
         */
        std::unique_ptr<Behaviour> create_behaviour(const std::string& name) const;

        /**
         * Creates and returns an instance of the behaviour registered to the provided behaviour type.
         *
         * @return Instance of the behaviour associated with the provided behaviour type.
         */
        template<typename BehaviourType>
        std::unique_ptr<BehaviourType> create_behaviour() const
        {
            static_assert(std::is_base_of<Attribute, BehaviourType>::value, "Template parameter BehaviourType in"
                    " ComponentRegistry::create_behaviour is not derived from Behaviour");

            return std::dynamic_pointer_cast<std::unique_ptr<BehaviourType>>(create_behaviour(Type<BehaviourType>::name()));
        }

    private:
        /**
         * Component factory registry.
         *
         * Maps components by name to their factory instances.
         */
        FactoryRegistry m_factory_registry;
    };

    /**
     * Returns a reference to the single component registry instance.
     *
     * @return Reference to the component registry.
     */
    inline ComponentRegistry& component_registry()
    {
        static ComponentRegistry instance;
        return instance;
    }

    /**
     * Minimal templated class used for registering components outside of `main()`.
     *
     * To use, just instantiate the class with the required component type provided as the template argument.
     */
    template<typename ComponentType>
    class ComponentRegistration
    {
    public:
        /**
         * Constructor.
         *
         * @param factory Factory to use for instantiating components of the provided template type.
         */
        ComponentRegistration(std::unique_ptr<ComponentFactory> factory)
        {
            component_registry().register_component<ComponentType>(std::move(factory));
        }

        /**
         * Constructor.
         *
         * @param name Name to be associated with the templated component type.
         * @param factory Factory to use for instantiating components of the specified name.
         */
        ComponentRegistration(const std::string& name, std::unique_ptr<ComponentFactory> factory)
        {
            component_registry().register_component<ComponentType>(name, std::move(factory));
        }
    };
}

#endif