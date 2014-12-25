#ifndef SUBORBITAL_EXAMPLE_ATTRIBUTE_HPP
#define SUBORBITAL_EXAMPLE_ATTRIBUTE_HPP

#include <string>

#include <suborbital/component/Attribute.hpp>

namespace suborbital
{
    /**
     * A primitive attribute used for testing purposes.
     */
    class ExampleAttribute : public Attribute
    {
    public:
        /**
         * Constructor.
         */
        ExampleAttribute();

        /**
         * Destructor.
         */
        ~ExampleAttribute();

        /**
         * Called after the attribute has been created and assigned to the entity.
         */
        void create();

        /**
         * Accessor for the value stored within the attribute.
         *
         * @return Value stored within the attribute.
         */
        const std::string& value() const;

        /**
         * Sets the value stored within the attribute.
         *
         * @param s Value to store within the attribute.
         */
        void value(const std::string& s);

        /**
         * Prints the value stored within the attribute to the console.
         */
        void log() const;

    private:
        /**
         * Value stored within the attribute.
         */
        std::string m_value;
    };
}

#endif