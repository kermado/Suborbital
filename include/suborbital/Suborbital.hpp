#ifndef SUBORBITAL_HPP
#define SUBORBITAL_HPP

#include <suborbital/Entity.hpp>

#include <suborbital/component/ComponentRegistry.hpp>
#include <suborbital/component/PythonAttributeFactory.hpp>
#include <suborbital/component/PythonBehaviourFactory.hpp>

/**
 * Macro for registering an attribute type. This is necessary for creating attributes inside of scripts.
 *
 * @param TYPE Behaviour type.
 */
#define REGISTER_ATTRIBUTE(T)                                                                                          \
    TYPE(T);                                                                                                           \
    namespace {                                                                                                        \
        std::unique_ptr<AttributeFactory<T>> factory(new AttributeFactory<T>());                                       \
        ComponentRegistration<T> registration(std::move(factory));                                                     \
    }                                                                                                                  \

/**
 * Macro for registering a behaviour type. This is necessary for creating behaviours inside of scripts.
 *
 * @param T Behaviour type.
 */
#define REGISTER_BEHAVIOUR(T)                                                                                          \
    TYPE(T);                                                                                                           \
    namespace {                                                                                                        \
        std::unique_ptr<BehaviourFactory<T>> factory(new BehaviourFactory<T>());                                       \
        ComponentRegistration<T> registration(std::move(factory));                                                     \
    }                                                                                                                  \

/**
 * Macro for registering a Python defined behaviour type.
 *
 * @param NAME File/class name for the behaviour to register.
 */
#define REGISTER_PYTHON_BEHAVIOUR(NAME)                                                                                \
	{                                                                                                                  \
        std::unique_ptr<BehaviourFactory<PythonBehaviour>> factory(new BehaviourFactory<PythonBehaviour>(NAME));       \
        ComponentRegistration<TYPE> registration(NAME, std::move(factory));                                            \
    }                                                                                                                  \


#endif