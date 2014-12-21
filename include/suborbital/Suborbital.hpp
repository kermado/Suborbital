#ifndef SUBORBITAL_HPP
#define SUBORBITAL_HPP

#include <suborbital/Entity.hpp>
#include <suborbital/BehaviourRegistry.hpp>
#include <suborbital/BehaviourFactory.hpp>

/**
 * Macro for registering a behaviour type to a string name. This is necessary for creating behaviours inside of scripts.
 *
 * @param TYPE Behaviour type.
 * @param NAME Name to associate with the behaviour type.
 */
#define REGISTER_BEHAVIOUR(TYPE, NAME)                                                                                 \
	{                                                                                                                  \
        std::unique_ptr<BehaviourFactory<TYPE>> factory(new BehaviourFactory<TYPE>());                                 \
        behaviour_registry().register_behaviour(NAME, std::move(factory));                                             \
    }                                                                                                                  \

/**
 * Macro for registering a Python defined behaviour type.
 *
 * @param NAME File/class name for the behaviour to register.
 */
#define REGISTER_PYTHON_BEHAVIOUR(NAME)                                                                                \
	{                                                                                                                  \
        std::unique_ptr<BehaviourFactory<PythonBehaviour>> factory(new BehaviourFactory<PythonBehaviour>(NAME));       \
        behaviour_registry().register_behaviour(NAME, std::move(factory));                                             \
    }                                                                                                                  \


#endif