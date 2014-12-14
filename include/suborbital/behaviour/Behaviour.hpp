#ifndef BEHAVIOUR_HPP
#define BEHAVIOUR_HPP

#include <string>
#include <cassert>
#include <memory>
#include <functional>
#include <typeindex>
#include <unordered_map>

#include <suborbital/NonCopyable.hpp>

/**
 * Macro for registering a behaviour type to a string name. This is necessary for creating behaviours inside of scripts.
 *
 * @param TYPE Behaviour type.
 * @param NAME Name to associate with the behaviour type.
 */
#define REGISTER_BEHAVIOUR(TYPE, NAME)                                                                                 \
	namespace detail {                                                                                                 \
	namespace                                                                                                          \
	{                                                                                                                  \
		template<class T>                                                                                              \
		class BehaviourRegistration;                                                                                   \
                                                                                                                       \
		template<>                                                                                                     \
		class BehaviourRegistration<TYPE>                                                                              \
		{                                                                                                              \
			static const RegistryEntry<TYPE>& registration;                                                            \
		};                                                                                                             \
                                                                                                                       \
		const RegistryEntry<TYPE>& BehaviourRegistration<TYPE>::registration = RegistryEntry<TYPE>::get(NAME);         \
	}}

namespace suborbital
{
    // Forward declarations.
    class Entity;

    namespace behaviour
    {
        /**
         * The base class for everything attached to entities.
         */
        class Behaviour : private NonCopyable
        {
        friend Entity;
        public:
            /**
             * Destructor.
             */
            virtual ~Behaviour();

            /**
             * Called after the behaviour has been created and assigned to the entity.
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
             * Accessor for the parent entity that the behaviour belongs to.
             *
             * @note The behaviour lifetime is tied to its parent entity.
             *
             * @return Pointer to the parent entity.
             */
            Entity* entity() const;

        protected:
            /**
             * Constructor.
             */
            Behaviour();

        private:
            /**
             * Pointer to the parent entity.
             * Note that the behaviour lifetime is tied to its parent entity.
             */
            Entity* m_entity;
        };
        /**
         * Internal details.
         */
        namespace detail
        {
            /**
             * Behaviour factory function typedef.
             */
            typedef std::function<std::unique_ptr<Behaviour>()> BehaviourFactory;

            /**
             * Behaviour registry.
             *
             * Represents the behaviour registry where behaviours are registered.
             */
            class BehaviourRegistry
            {
            private:
                typedef std::unordered_map<std::type_index, std::string> BehaviourNameRegistry;
                typedef std::unordered_map<std::string, BehaviourFactory> BehaviourFactoryRegistry;

            public:
                /**
                 * Constructor.
                 */
                BehaviourRegistry()
                : m_name_registry()
                , m_factory_registry()
                {
                    // Nothing to do.
                }

                /**
                 * Registers the provided behaviour type to the specified behaviour name and behaviour factory.
                 *
                 * @param behaviour_name Name to associate with the provided behaviour type.
                 * @param behaviour_factory Factory function to use for instantiating behaviours of the specified name.
                 */
                template<typename BehaviourType>
                void register_behaviour(const std::string& behaviour_name, const BehaviourFactory& behaviour_factory)
                {
                    m_name_registry.insert(BehaviourNameRegistry::value_type(typeid(BehaviourType), behaviour_name));
                    m_factory_registry.insert(BehaviourFactoryRegistry::value_type(behaviour_name, behaviour_factory));
                }

                /**
                 * Registers the supplied behaviour factory function to the specified behaviour name.
                 *
                 * @note This method does not register the specified behaviour name to a specific c++ type. This
                 * function is used for registering scripted behaviours.
                 *
                 * @param behaviour_name Name to associate with the provided behaviour factory function.
                 * @param behaviour_factory Factory function to use for instantiating behaviours of the specified name.
                 */
                void register_behaviour(const std::string& behaviour_name, const BehaviourFactory& behaviour_factory)
                {
                    m_factory_registry.insert(BehaviourFactoryRegistry::value_type(behaviour_name, behaviour_factory));
                }

                /**
                 * Accessor for the behaviour name associated with the provided behaviour type.
                 *
                 * @note This function is only useful for obtaining the name associated with c++ defined behaviours. It
                 * is not possible to find the name associated with behaviours defined in scripts.
                 *
                 * @return Name associated with the provided behaviour type. An empty string is returned if the provided
                 * behaviour type has not been registered.
                 */
                template<typename BehaviourType>
                std::string behaviour_name() const
                {
                    auto iter = m_name_registry.find(std::type_index(typeid(BehaviourType)));
                    if (iter != m_name_registry.end())
                    {
                        return iter->second;
                    }

                    return ""; // Unable to find the name registered to the specified BehaviourType.
                }

                /**
                 * Accessor for the behaviour factory function registered to the specified behaviour name.
                 *
                 * @note This function is intended to be used for obtaining factory functions for behaviours defined
                 * within scripts.
                 *
                 * @param behaviour_name Name of the behaviour for which to return the associated factory function.
                 * @return Behaviour factory function for the behaviour associated with the specified behaviour name.
                 */
                BehaviourFactory behaviour_factory(const std::string& behaviour_name) const
                {
                    auto iter = m_factory_registry.find(behaviour_name);
                    if (iter != m_factory_registry.end())
                    {
                        return iter->second;
                    }

                    return nullptr;
                }

                /**
                 * Accessor for the behaviour factory function registered to the provided behaviour type.
                 *
                 * @return Behaviour factory function for the provided behaviour type.
                 */
                template<typename BehaviourType>
                BehaviourFactory behaviour_factory() const
                {
                    const std::string class_name = behaviour_name<BehaviourType>();
                    if (class_name.length() > 0)
                    {
                        return behaviour_factory(class_name);
                    }

                    return nullptr;
                }

            private:
                /**
                 * Behaviour name registry.
                 * Maps behaviour types to behaviour names.
                 */
                BehaviourNameRegistry m_name_registry;

                /**
                 * Behaviour factory registry.
                 * Maps behaviour names to behaviour factories.
                 */
                BehaviourFactoryRegistry m_factory_registry;
            };

            /**
             * Returns a reference to the single behaviour registry instance.
             *
             * @return Reference to the behaviour registry.
             */
            inline BehaviourRegistry& behaviour_registry()
            {
                static BehaviourRegistry instance;
                return instance;
            }

            /**
             * Entry for a behaviour type in the behaviour registry.
             */
            template<class BehaviourType>
            struct RegistryEntry : private NonCopyable
            {
            public:
                /**
                 * Accessor for the single registry entry for the behaviour type.
                 *
                 * @param name Name associated with the behaviour type.
                 */
                static RegistryEntry<BehaviourType>& get(const std::string& name)
                {
                    static RegistryEntry<BehaviourType> instance(name);
                    return instance;
                }

            private:
                /**
                 * Constructor.
                 *
                 * @param behaviour_name Name to associate with the behaviour type.
                 */
                RegistryEntry(const std::string& behaviour_name)
                {
                    // Get the behaviour registry.
                    BehaviourRegistry& registry = behaviour_registry();

                    // Create the behaviour factory function.
                    BehaviourFactory factory = []() {
                        return std::unique_ptr<BehaviourType>(new BehaviourType());
                    };

                    // Register the behaviour.
                    registry.register_behaviour<BehaviourType>(behaviour_name, factory);
                }
            };
        }

        /**
         * Creates a behaviour of type specified by `class_name`.
         *
         * Note that this method should not be called directly. Instead, you should create behaviours through entities.
         *
         * @param class_name Class name for the behaviour to be created.
         * @return Unique pointer to the created behaviour.
         */
        std::unique_ptr<Behaviour> create(const std::string&class_name);

        /**
         * Accessor for the name registered to the specified behaviour type.
         *
         * @return Name registered to the provided behaviour type.
         */
        template<typename BehaviourType>
        std::string name()
        {
            detail::BehaviourRegistry &registry = detail::behaviour_registry();
            return registry.behaviour_name<BehaviourType>();
        }
    }
}

#endif