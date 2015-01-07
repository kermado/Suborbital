#include <iostream>

#include <suborbital/component/ExampleAttribute.hpp>

namespace suborbital
{
    ExampleAttribute::ExampleAttribute()
    : Attribute()
    , m_value()
    {
        std::cout << "ExampleAttribute::ExampleAttribute()" << std::endl;
    }

    ExampleAttribute::~ExampleAttribute()
    {
        std::cout << "ExampleAttribute::~ExampleAttribute()" << std::endl;
    }

    void ExampleAttribute::create()
    {
        // Nothing to do.
    }

    const std::string& ExampleAttribute::value() const
    {
        return m_value;
    }

    void ExampleAttribute::value(const std::string& s)
    {
        m_value = s;
    }

    void ExampleAttribute::log() const
    {
        std::cout << "ExampleAttribute holds the value: \"" << m_value << "\"" << std::endl;
    }
}