#include <cassert>
#include <iostream>

#include <suborbital/Suborbital.hpp>
#include <suborbital/Entity.hpp>
#include <suborbital/behaviour/Behaviour.hpp>

namespace suborbital
{
    namespace behaviour
    {
        Behaviour::Behaviour()
        : m_entity(nullptr)
        {
            std::cout << "Behaviour::Behaviour()" << std::endl;
        }

        Behaviour::~Behaviour()
        {
            std::cout << "Behaviour::~Behaviour()" << std::endl;
        }

        void Behaviour::log(const std::string& message) const
        {
            std::cout << message << std::endl;
        }

        Entity* Behaviour::entity() const
        {
            return m_entity;
        }

        std::unique_ptr<Behaviour> create(const std::string& class_name)
        {
            // Try to get the behaviour registration for the specified class name.
            detail::BehaviourRegistry& registry = detail::behaviour_registry();
            detail::BehaviourFactory factory = registry.behaviour_factory(class_name);

            // If a behaviour registration for the class name exists then we can instantiate the behaviour using the
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