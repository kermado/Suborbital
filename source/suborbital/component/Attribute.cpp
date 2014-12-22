#include <iostream>

#include <suborbital/component/Attribute.hpp>

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