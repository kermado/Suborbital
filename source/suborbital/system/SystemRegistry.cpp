#include <suborbital/system/SystemRegistry.hpp>
#include <suborbital/system/SystemFactory.hpp>
#include <suborbital/system/PythonSystemFactory.hpp>

namespace suborbital
{
    SystemRegistry::SystemRegistry()
    : m_name_registry()
    , m_factory_registry()
    {
        // Nothing to do.
    }

    SystemRegistry::~SystemRegistry()
    {
        // Nothing to do.
    }

    void SystemRegistry::register_system(const std::string& name, std::unique_ptr<SystemFactory> factory)
    {
        m_factory_registry.insert(FactoryRegistry::value_type(name, std::move(factory)));
    }

    std::unique_ptr<System> SystemRegistry::create_system(const std::string& name) const
    {
        // We will first attempt to instantiate the system registered under the supplied name.
        auto iter = m_factory_registry.find(name);
        if (iter != m_factory_registry.end())
        {
            return iter->second->create();
        }

        // If no system was registered under the supplied name then we attempt to instantiate a scripted system.
        // Note that the factory's create function will return a nullptr in the event that it is unable to instantiate
        // the attribute.
        SpecificSystemFactory<PythonSystem> factory(name);
        return factory.create();
    }
}