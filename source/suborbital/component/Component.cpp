#include <cassert>
#include <iostream>

#include <suborbital/Suborbital.hpp>
#include <suborbital/Entity.hpp>
#include <suborbital/component/Component.hpp>

namespace suborbital
{
    namespace component
    {
        Component::Component()
        : m_entity()
        {
            std::cout << "Component::Component()" << std::endl;
        }

        Component::~Component()
        {
            std::cout << "Component::~Component()" << std::endl;
        }

        void Component::log(const std::string& message) const
        {
            std::cout << message << std::endl;
        }

        std::weak_ptr<Entity> Component::entity() const
        {
            return m_entity;
        }

        std::unique_ptr<Component> create(const std::string& class_name)
        {
            // Try to get the component registration for the specified class name.
            detail::ComponentRegistry& registry = detail::component_registry();
            detail::ComponentFactory factory = registry.component_factory(class_name);

            // If a component registration for the class name exists then we can instantiate the component using the
            // corresponding factory function. Otherwise, we look to see whether we can find a script that defines the
            // specified class name.
            if (factory)
            {
                return factory();
            }
            else
            {
                return script_interpreter.create(class_name);
            }
        }
    }
}