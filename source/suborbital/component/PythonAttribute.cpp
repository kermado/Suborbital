#include <iostream>
#include <Python.h>

#include <suborbital/component/PythonAttribute.hpp>

namespace suborbital
{
    PythonAttribute::PythonAttribute()
    : Attribute()
    , derived(nullptr)
    {
        std::cout << "PythonAttribute::PythonAttribute()" << std::endl;
    }

    PythonAttribute::~PythonAttribute()
    {
        std::cout << "PythonAttribute::PythonAttribute()" << std::endl;

        if (derived != nullptr)
        {
            Py_DECREF(derived);
        }
    }
}