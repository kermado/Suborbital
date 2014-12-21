#include <iostream>

#include <suborbital/Attribute.hpp>

namespace suborbital
{
    Attribute::Attribute()
    : Component()
    {
        std::cout << "Attribute::Attribute()" << std::endl;
    }

    Attribute::~Attribute()
    {
        std::cout << "Attribute::~Attribute()" << std::endl;
    }
}