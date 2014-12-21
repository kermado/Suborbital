#include <suborbital/BehaviourRegistry.hpp>
#include <suborbital/BehaviourFactory.hpp>

namespace suborbital
{
    BehaviourRegistry::BehaviourRegistry()
    : m_name_registry()
    , m_factory_registry()
    {
        // Nothing to do.
    }

    BehaviourRegistry::~BehaviourRegistry()
    {
        // Nothing to do.
    }

    bool BehaviourRegistry::behaviour_registered(const std::string& behaviour_name) const
    {
        if (behaviour_name.length() <= 0) return false;

        auto iter = m_factory_registry.find(behaviour_name);
        if (iter != m_factory_registry.end())
        {
            return iter->second != nullptr;
        }

        return false;
    }

    void BehaviourRegistry::register_behaviour(const std::string& behaviour_name, std::unique_ptr<IBehaviourFactory> behaviour_factory)
    {
        assert(behaviour_registered(behaviour_name) == false);
        m_factory_registry.insert(BehaviourFactoryRegistry::value_type(behaviour_name, std::move(behaviour_factory)));
    }

    std::unique_ptr<Behaviour> BehaviourRegistry::create_behaviour(const std::string& behaviour_name) const
    {
        // We will first attempt to instantiate a behaviour registered under the supplied name.
        auto iter = m_factory_registry.find(behaviour_name);
        if (iter != m_factory_registry.end())
        {
            return iter->second->create();
        }

        // If no behaviour was registered under the supplied name then we attempt to instantiate a scripted behaviour.
        // Note that the factory's create function will return a nullptr in the event that it is unable to instantiate
        // the behaviour.
        BehaviourFactory<PythonBehaviour> factory(behaviour_name);
        return factory.create();
    }
}