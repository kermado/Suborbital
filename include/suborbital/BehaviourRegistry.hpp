#ifndef SUBORBITAL_BEHAVIOUR_REGISTRY_HPP
#define SUBORBITAL_BEHAVIOUR_REGISTRY_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include <typeindex>

#include <suborbital/NonCopyable.hpp>

namespace suborbital
{
    class Behaviour;
    class IBehaviourFactory;

    /**
     * Behaviour registry.
     *
     * Represents the behaviour registry where behaviours are registered.
     */
    class BehaviourRegistry : public NonCopyable
    {
    private:
        typedef std::unordered_map<std::type_index, std::string> BehaviourNameRegistry;
        typedef std::unordered_map<std::string, std::unique_ptr<IBehaviourFactory>> BehaviourFactoryRegistry;

    public:
        /**
         * Constructor.
         */
        BehaviourRegistry();

        /**
         * Destructor.
         */
        ~BehaviourRegistry();

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
         * Checks whether a behaviour has been registered under the specified behaviour name.
         *
         * @param behaviour_name Name for the behaviour.
         * @return True if a behaviour class has been registered under the specified name, false otherwise.
         */
        bool behaviour_registered(const std::string& behaviour_name) const;

        /**
         * Checks whether the provided behaviour type has been registered.
         *
         * @return True if the provided behaviour type has been registered, false otherwise.
         */
        template<typename BehaviourType>
        bool behaviour_registered() const
        {
            const std::string registered_name = behaviour_name<BehaviourType>();
            if (registered_name.length() > 0)
            {
                return behaviour_registered(registered_name);
            }

            return false;
        }

        /**
         * Registers the provided behaviour type to the specified behaviour name and behaviour factory.
         *
         * @param behaviour_name Name to associate with the provided behaviour type.
         * @param behaviour_factory Factory to use for instantiating behaviours of the specified name.
         */
        template<typename BehaviourType>
        void register_behaviour(const std::string& behaviour_name, std::unique_ptr<IBehaviourFactory> behaviour_factory)
        {
            assert(behaviour_registered<BehaviourType>() == false);
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
         * @param behaviour_factory Factory to use for instantiating behaviours of the specified name.
         */
        void register_behaviour(const std::string& behaviour_name, std::unique_ptr<IBehaviourFactory> behaviour_factory);

        /**
         * Creates and returns an instance of the behaviour registered to the provided behaviour name.
         *
         * This function will return a nullptr if no behaviour has been registered with the provided `behaviour_name`.
         *
         * @note This function is intended to be used for creating behaviours defined within scripts.
         *
         * @param behaviour_name Name of the behaviour for which to create.
         * @return Instance of the behaviour associated with the specified behaviour name.
         */
        std::unique_ptr<Behaviour> create_behaviour(const std::string& behaviour_name) const;

        /**
         * Creates and returns an instance of the behaviour registered to the provided behaviour type.
         *
         * This function will return a nullptr if no behaviour has been registered with the provided `behaviour_name`.
         *
         * @return Instance of the behaviour associated with the provided behaviour type.
         */
        template<typename BehaviourType>
        std::unique_ptr<Behaviour> create_behaviour() const
        {
            const std::string registered_name = behaviour_name<BehaviourType>();
            if (registered_name.length() > 0)
            {
                return create_behaviour(registered_name);
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
}

#endif