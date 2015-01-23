#ifndef SUBORBITAL_SYSTEM_FACTORY_HPP
#define SUBORBITAL_SYSTEM_FACTORY_HPP

#include <memory>

namespace suborbital
{
    // Forward declarations.
    class System;

    /**
     * The base class for factories that instantiate systems.
     */
    class SystemFactory
    {
    public:
        /**
         * Constructor.
         */
        SystemFactory() = default;

        /**
         * Destructor.
         */
        virtual ~SystemFactory() = default;

        /**
         * Instantiates a system and returns a unique_ptr to the created system.
         *
         * @return Unique pointer to the created system.
         */
        virtual std::unique_ptr<System> create() const = 0;
    };
}

#endif