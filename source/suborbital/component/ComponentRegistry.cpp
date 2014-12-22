#include <cassert>

#include <suborbital/component/ComponentRegistry.hpp>
#include <suborbital/component/AttributeFactory.hpp>
#include <suborbital/component/PythonBehaviourFactory.hpp>
#include <suborbital/component/PythonAttributeFactory.hpp>

namespace suborbital
{
    ComponentRegistry::ComponentRegistry()
    : m_name_registry()
    , m_factory_registry()
    {
        // Nothing to do.
    }

    ComponentRegistry::~ComponentRegistry()
    {
        // Nothing to do.
    }

    void ComponentRegistry::register_component(const std::string& name, std::unique_ptr<ComponentFactory> factory)
    {
        m_factory_registry.insert(FactoryRegistry::value_type(name, std::move(factory)));
    }

    std::unique_ptr<Attribute> ComponentRegistry::create_attribute(const std::string& name) const
    {
        // We will first attempt to instantiate an attribute registered under the supplied name.
        auto iter = m_factory_registry.find(name);
        if (iter != m_factory_registry.end())
        {
            std::unique_ptr<Component> component = iter->second->create();
            return std::unique_ptr<Attribute>(dynamic_cast<Attribute*>(component.release()));
        }

        // If no attribute was registered under the supplied name then we attempt to instantiate a scripted attribute.
        // Note that the factory's create function will return a nullptr in the event that it is unable to instantiate
        // the attribute.
        AttributeFactory<PythonAttribute> factory(name);
        return std::unique_ptr<Attribute>(dynamic_cast<Attribute*>(factory.create().release()));
    }

    std::unique_ptr<Behaviour> ComponentRegistry::create_behaviour(const std::string& name) const
    {
        // We will first attempt to instantiate a behaviour registered under the supplied name.
        auto iter = m_factory_registry.find(name);
        if (iter != m_factory_registry.end())
        {
            std::unique_ptr<Component> component = iter->second->create();
            return std::unique_ptr<Behaviour>(dynamic_cast<Behaviour*>(component.release()));
        }

        // If no behaviour was registered under the supplied name then we attempt to instantiate a scripted behaviour.
        // Note that the factory's create function will return a nullptr in the event that it is unable to instantiate
        // the behaviour.
        BehaviourFactory<PythonBehaviour> factory(name);
        return std::unique_ptr<Behaviour>(dynamic_cast<Behaviour*>(factory.create().release()));
    }
}