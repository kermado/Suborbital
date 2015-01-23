#ifndef SUBORBITAL_SYSTEM_REGISTRY_HPP
#define SUBORBITAL_SYSTEM_REGISTRY_HPP

#include <string>
#include <memory>
#include <cassert>
#include <unordered_map>
#include <typeindex>

#include <suborbital/NonCopyable.hpp>

namespace suborbital
{
    // Forward declarations.
    class System;
    class SystemFactory;

    /**
     * System Registry
     */
    class SystemRegistry : public NonCopyable
    {
    private:
        /**
         * System names registry type definition.
         */
        typedef std::unordered_map<std::type_index, std::string> NameRegistry;

        /**
         * System factories registry type definition.
         */
        typedef std::unordered_map<std::string, std::unique_ptr<SystemFactory>> FactoryRegistry;

    public:
        /**
         * Constructor.
         */
        SystemRegistry();

        /**
         * Destructor.
         */
        ~SystemRegistry();

        /**
         * Accessor for the name associated with the provided system type.
         *
         * @note This function is only useful for obtaining the name associated with c++ defined systems. It is not
         * possible to find the name associated with systems defined in scripts.
         *
         * @return Name associated with the provided system type.
         */
        template<typename SystemType>
        std::string system_name() const
        {
            static_assert(std::is_base_of<System, SystemType>::value, "Template parameter SystemType in"
                    " SystemRegistry::system_name is not derived from System");

            auto iter = m_name_registry.find(std::type_index(typeid(SystemType)));
            assert(iter != m_name_registry.end());

            return iter->second;
        }

        /**
         * Registers the provided system type to the specified name and factory.
         *
         * @param name Name to associate with the provided system type.
         * @param factory Factory to use for instantiating systems of the specified name.
         */
        template<typename SystemType>
        void register_system(const std::string& name, std::unique_ptr<SystemFactory> factory)
        {
            static_assert(std::is_base_of<System, SystemType>::value, "Template parameter SystemType in"
                    " SystemRegistry::register_system is not derived from System");

            m_name_registry.insert(NameRegistry::value_type(typeid(SystemType), name));
            m_factory_registry.insert(FactoryRegistry::value_type(name, std::move(factory)));
        }

        /**
         * Registers the supplied system factory function to the specified name.
         *
         * @note This function does not register the specified system name to a specific c++ type. This function is
         * used for registering scripted systems.
         *
         * @param name Name to associate with the provided system factory function.
         * @param factory Factory to use for instantiating systems of the specified name.
         */
        void register_system(const std::string& name, std::unique_ptr<SystemFactory> factory);

        /**
         * Creates and returns an instance of the system registered to the provided name.
         *
         * @param name Name of the system that should be created.
         * @return Instance of the system specified by the provided system name.
         */
        std::unique_ptr<System> create_system(const std::string& name) const;

        /**
         * Creates and returns an instance of the system registered to the provided system type.
         *
         * @return Instance of the system specified by the provided system type.
         */
        template<typename SystemType>
        std::unique_ptr<SystemType> create_system() const
        {
            static_assert(std::is_base_of<System, SystemType>::value, "Template parameter SystemType in"
                    " SystemRegistry::create_system is not derived from System");

            return std::dynamic_pointer_cast<std::unique_ptr<SystemType>>(create_system(system_name<SystemType>()));
        }

    private:
        /**
         * System name registry.
         *
         * Maps system types to their registered names.
         */
        NameRegistry m_name_registry;

        /**
         * System factory registry.
         *
         * Maps systems by name to their factory instances.
         */
        FactoryRegistry m_factory_registry;
    };

    /**
     * Returns a reference to the single system registry instance.
     *
     * @return Reference to the system registry.
     */
    inline SystemRegistry& system_registry()
    {
        static SystemRegistry instance;
        return instance;
    }
}

#endif