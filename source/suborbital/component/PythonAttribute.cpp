#include <iostream>

#include <suborbital/component/PythonAttribute.hpp>

namespace suborbital
{
    PythonAttribute::PythonAttribute()
    : Attribute()
    {
        std::cout << "PythonAttribute::PythonAttribute()" << std::endl;
    }

    PythonAttribute::~PythonAttribute()
    {
        std::cout << "PythonAttribute::~PythonAttribute()" << std::endl;
        //std::cout << "BEFORE DECREF: " << derived->ob_refcnt << std::endl;
        Py_XDECREF(derived);
        //std::cout << "AFTER DECREF: " << derived->ob_refcnt << std::endl;
    }
}