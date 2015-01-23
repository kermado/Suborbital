#ifndef SUBORBITAL_SPECIFIC_SYSTEM_FACTORY_HPP
#define SUBORBITAL_SPECIFIC_SYSTEM_FACTORY_HPP

#include <suborbital/system/SystemFactory.hpp>

namespace suborbital
{
    // Forward declarations.
    class System;

    template<typename SystemType>
    class SpecificSystemFactory : public SystemFactory
    {
    public:
        /**
         * Constructor.
         */
        SpecificSystemFactory() = default;

        /**
         * Destructor.
         */
        ~SpecificSystemFactory() = default;

        /**
         * Instantiates a system of the templated type and returns a unique_ptr to the created system.
         *
         * @return Unique pointer to the created system.
         */
        std::unique_ptr<System> create() const
        {
            return std::unique_ptr<SystemType>(new SystemType());
        }
    };
}

#endif