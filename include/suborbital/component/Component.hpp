#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>
#include <cassert>
#include <memory>
#include <functional>
#include <typeindex>
#include <unordered_map>

#include <suborbital/NonCopyable.hpp>

/**
 * Macro for registering a component type to a string name. This is necessary for creating components inside of scripts.
 *
 * @param TYPE Component type.
 * @param NAME Name to associate with the component type.
 */
#define REGISTER_COMPONENT(TYPE, NAME)                                                                                 \
	namespace detail {                                                                                                 \
	namespace                                                                                                          \
	{                                                                                                                  \
		template<class T>                                                                                              \
		class ComponentRegistration;                                                                                   \
                                                                                                                       \
		template<>                                                                                                     \
		class ComponentRegistration<TYPE>                                                                              \
		{                                                                                                              \
			static const RegistryEntry<TYPE>& registration;                                                            \
		};                                                                                                             \
                                                                                                                       \
		const RegistryEntry<TYPE>& ComponentRegistration<TYPE>::registration = RegistryEntry<TYPE>::get(NAME);         \
	}}

namespace suborbital
{
    // Forward declarations.
    class Entity;

    namespace component
    {
        /**
         * The base class for everything attached to entities.
         */
        class Component : private NonCopyable
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
             * Called each frame.
             *
             * @param dt Time elapsed (in seconds) since the previous call to update.
             */
            virtual void update(double dt) = 0;

            /**
             * Logs a message.
             *
             * @param message Message to print to the log.
             */
            void log(const std::string&message) const;

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
             * Note that the component lifetime is tied to its parent entity.
             */
            Entity* m_entity;
        };
        /**
         * Internal details.
         */
        namespace detail
        {
            /**
             * Component factory function typedef.
             */
            typedef std::function<std::unique_ptr<Component>()> ComponentFactory;

            /**
             * Component registry.
             *
             * Represents the component registry where components are registered.
             */
            class ComponentRegistry
            {
            private:
                typedef std::unordered_map<std::type_index, std::string> ComponentNameRegistry;
                typedef std::unordered_map<std::string, ComponentFactory> ComponentFactoryRegistry;

            public:
                /**
                 * Constructor.
                 */
                ComponentRegistry()
                : m_name_registry()
                , m_factory_registry()
                {
                    // Nothing to do.
                }

                /**
                 * Registers the provided component type to the specified component name and component factory.
                 *
                 * @param component_name Name to associate with the provided component type.
                 * @param component_factory Factory function to use for instantiating components of the specified name.
                 */
                template<typename ComponentType>
                void register_component(const std::string& component_name, const ComponentFactory& component_factory)
                {
                    m_name_registry.insert(ComponentNameRegistry::value_type(typeid(ComponentType), component_name));
                    m_factory_registry.insert(ComponentFactoryRegistry::value_type(component_name, component_factory));
                }

                /**
                 * Registers the supplied component factory function to the specified component name.
                 *
                 * @note This method does not register the specified component name to a specific c++ type. This
                 * function is used for registering scripted components.
                 *
                 * @param component_name Name to associate with the provided component factory function.
                 * @param component_factory Factory function to use for instantiating components of the specified name.
                 */
                void register_component(const std::string& component_name, const ComponentFactory& component_factory)
                {
                    m_factory_registry.insert(ComponentFactoryRegistry::value_type(component_name, component_factory));
                }

                /**
                 * Accessor for the component name associated with the provided component type.
                 *
                 * @note This function is only useful for obtaining the name associated with c++ defined components. It
                 * is not possible to find the name associated with components defined in scripts.
                 *
                 * @return Name associated with the provided component type. An empty string is returned if the provided
                 * component type has not been registered.
                 */
                template<typename ComponentType>
                std::string component_name() const
                {
                    auto iter = m_name_registry.find(std::type_index(typeid(ComponentType)));
                    if (iter != m_name_registry.end())
                    {
                        return iter->second;
                    }

                    return ""; // Unable to find the name registered to the specified ComponentType.
                }

                /**
                 * Accessor for the component factory function registered to the specified component name.
                 *
                 * @note This function is intended to be used for obtaining factory functions for components defined
                 * within scripts.
                 *
                 * @param component_name Name of the component for which to return the associated factory function.
                 * @return Component factory function for the component associated with the specified component name.
                 */
                ComponentFactory component_factory(const std::string& component_name) const
                {
                    auto iter = m_factory_registry.find(component_name);
                    if (iter != m_factory_registry.end())
                    {
                        return iter->second;
                    }

                    return nullptr;
                }

                /**
                 * Accessor for the component factory function registered to the provided component type.
                 *
                 * @return Component factory function for the provided component type.
                 */
                template<typename ComponentType>
                ComponentFactory component_factory() const
                {
                    const std::string class_name = component_name<ComponentType>();
                    if (class_name.length() > 0)
                    {
                        return component_factory(class_name);
                    }

                    return nullptr;
                }

            private:
                /**
                 * Component name registry.
                 * Maps component types to component names.
                 */
                ComponentNameRegistry m_name_registry;

                /**
                 * Component factory registry.
                 * Maps component names to component factories.
                 */
                ComponentFactoryRegistry m_factory_registry;
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
             * Entry for a component type in the component registry.
             */
            template<class ComponentType>
            struct RegistryEntry : private NonCopyable
            {
            public:
                /**
                 * Accessor for the single registry entry for the component type.
                 *
                 * @param name Name associated with the component type.
                 */
                static RegistryEntry<ComponentType>& get(const std::string& name)
                {
                    static RegistryEntry<ComponentType> instance(name);
                    return instance;
                }

            private:
                /**
                 * Constructor.
                 *
                 * @param component_name Name to associate with the component type.
                 */
                RegistryEntry(const std::string& component_name)
                {
                    // Get the component registry.
                    ComponentRegistry& registry = component_registry();

                    // Create the component factory function.
                    ComponentFactory factory = []() {
                        return std::unique_ptr<ComponentType>(new ComponentType());
                    };

                    // Register the component.
                    registry.register_component<ComponentType>(component_name, factory);
                }
            };
        }

        /**
         * Creates a component of type specified by `class_name`.
         *
         * Note that this method should not be called directly. Instead, you should create components through entities.
         *
         * @param class_name Class name for the component to be created.
         * @return Unique pointer to the created component.
         */
        std::unique_ptr<Component> create(const std::string&class_name);

        /**
         * Accessor for the name registered to the specified component type.
         *
         * @return Name registered to the provided component type.
         */
        template<typename ComponentType>
        std::string name()
        {
            detail::ComponentRegistry &registry = detail::component_registry();
            return registry.component_name<ComponentType>();
        }
    }
}

#endif