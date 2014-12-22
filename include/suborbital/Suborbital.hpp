#ifndef SUBORBITAL_HPP
#define SUBORBITAL_HPP

#include <suborbital/Entity.hpp>
#include <suborbital/component/ComponentRegistry.hpp>
#include <suborbital/component/PythonBehaviourFactory.hpp>

/**
 * Macro for registering a behaviour type. This is necessary for creating behaviours inside of scripts.
 *
 * @param TYPE Behaviour type.
 */
#define REGISTER_BEHAVIOUR(TYPE)                                                                                       \
	{                                                                                                                  \
        std::unique_ptr<BehaviourFactory<TYPE>> factory(new BehaviourFactory<TYPE>());                                 \
        component_registry().register_component(#TYPE, std::move(factory));                                            \
    }                                                                                                                  \

/**
 * Macro for registering a Python defined behaviour type.
 *
 * @param NAME File/class name for the behaviour to register.
 */
#define REGISTER_PYTHON_BEHAVIOUR(NAME)                                                                                \
	{                                                                                                                  \
        std::unique_ptr<BehaviourFactory<PythonBehaviour>> factory(new BehaviourFactory<PythonBehaviour>(NAME));       \
        component_registry().register_component(NAME, std::move(factory));                                             \
    }                                                                                                                  \


#endif