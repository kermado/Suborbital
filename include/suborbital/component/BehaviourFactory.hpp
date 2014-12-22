#ifndef SUBORBITAL_BEHAVIOUR_FACTORY_HPP
#define SUBORBITAL_BEHAVIOUR_FACTORY_HPP

#include <iostream>

#include <suborbital/component/ComponentFactory.hpp>
#include <suborbital/component/Behaviour.hpp>

namespace suborbital
{
    template<typename BehaviourType>
    class BehaviourFactory : public ComponentFactory
    {
    public:
        BehaviourFactory() = default;
        ~BehaviourFactory() = default;

        std::unique_ptr<Component> create() const
        {
            static_assert(std::is_base_of<Behaviour, BehaviourType>::value,
                    "Template parameter BehaviourType in BehaviourFactory is not derived from Behaviour");
            return std::unique_ptr<BehaviourType>(new BehaviourType());
        }
    };
}

#endif