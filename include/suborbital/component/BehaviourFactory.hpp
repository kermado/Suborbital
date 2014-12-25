#ifndef SUBORBITAL_BEHAVIOUR_FACTORY_HPP
#define SUBORBITAL_BEHAVIOUR_FACTORY_HPP

#include <iostream>

#include <suborbital/component/ComponentFactory.hpp>
#include <suborbital/component/Behaviour.hpp>

namespace suborbital
{
    /**
     * Factory class for behaviours.
     *
     * This class is used internally for instantiating behaviours.
     */
    template<typename BehaviourType>
    class BehaviourFactory : public ComponentFactory
    {
    public:
        /**
         * Constructor.
         */
        BehaviourFactory() = default;

        /**
         * Destructor.
         */
        ~BehaviourFactory() = default;

        /**
         * Instantiates a behaviour of the provided type and returns a unique_ptr to the created behaviour.
         *
         * @note The caller is responsible for managing the lifetime of the returned behaviour.
         *
         * @return Unique pointer to the created behaviour.
         */
        std::unique_ptr<Component> create() const
        {
            static_assert(std::is_base_of<Behaviour, BehaviourType>::value,
                    "Template parameter BehaviourType in BehaviourFactory is not derived from Behaviour");
            return std::unique_ptr<BehaviourType>(new BehaviourType());
        }
    };
}

#endif