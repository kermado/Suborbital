#ifndef SUBORBITAL_COMPONENT_REGISTRY_HPP
#define SUBORBITAL_COMPONENT_REGISTRY_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include <typeindex>

#include <suborbital/NonCopyable.hpp>

namespace suborbital
{
    class Attribute;
    class Behaviour;
    class ComponentFactory;

    /**
     * Behaviour registry.
     *
     * Represents the behaviour registry where behaviours are registered.
     */
    class ComponentRegistry : public NonCopyable
    {
    private:
        typedef std::unordered_map<std::type_index, std::string> NameRegistry;
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
         * Accessor for the name associated with the provided component type.
         *
         * @note This function is only useful for obtaining the name associated with c++ defined components. It
         * is not possible to find the name associated with components defined in scripts.
         *
         * @return Name associated with the provided component type.
         */
        template<typename ComponentType>
        std::string component_name() const
        {
            auto iter = m_name_registry.find(std::type_index(typeid(ComponentType)));
            assert(iter != m_name_registry.end());

            return iter->second;
        }

        /**
         * Registers the provided component type to the specified name and factory.
         *
         * @param name Name to associate with the provided component type.
         * @param factory Factory to use for instantiating components of the specified name.
         */
        template<typename ComponentType>
        void register_component(const std::string& name, std::unique_ptr<ComponentFactory> factory)
        {
            m_name_registry.insert(NameRegistry::value_type(typeid(ComponentType), name));
            m_factory_registry.insert(FactoryRegistry::value_type(name, factory));
        }

        /**
         * Registers the supplied component factory function to the specified name.
         *
         * @note This method does not register the specified component name to a specific c++ type. This function is
         * used for registering scripted components.
         *
         * @param name Name to associate with the provided behaviour factory function.
         * @param factory Factory to use for instantiating behaviours of the specified name.
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
            return std::dynamic_pointer_cast<std::unique_ptr<AttributeType>>(create_attribute(component_name<AttributeType>()));
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
            return std::dynamic_pointer_cast<std::unique_ptr<BehaviourType>>(create_behaviour(component_name<BehaviourType>()));
        }

    private:
        /**
         * Component name registry.
         * Maps component types to their registered names.
         */
        NameRegistry m_name_registry;

        /**
         * Component factory registry.
         * Maps components by name to their creation factories.
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
}

#endif