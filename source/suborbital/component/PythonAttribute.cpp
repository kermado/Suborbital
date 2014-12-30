#include <iostream>

#include <suborbital/component/PythonAttribute.hpp>

namespace suborbital
{
    PythonAttribute::PythonAttribute()
    : PythonObject()
    , Attribute()
    {
        std::cout << "PythonAttribute::PythonAttribute()" << std::endl;
    }

    PythonAttribute::~PythonAttribute()
    {
        std::cout << "PythonAttribute::PythonAttribute()" << std::endl;
    }
}