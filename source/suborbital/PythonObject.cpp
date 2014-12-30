#include <iostream>

#include <suborbital/PythonObject.hpp>

namespace suborbital
{
    PythonObject::PythonObject()
    : derived(nullptr)
    {
        std::cout << "PythonObject::PythonObject()" << std::endl;
    }

    PythonObject::~PythonObject()
    {
        std::cout << "PythonObject::~PythonObject()" << std::endl;

        if (derived != nullptr)
        {
            Py_DECREF(derived);
        }
    }
}