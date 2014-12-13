#include <iostream>
#include <Python.h>

#include <suborbital/component/PythonComponent.hpp>

namespace suborbital
{
    namespace component
    {
        PythonComponent::PythonComponent()
        : Component()
        , derived(nullptr)
        {
            std::cout << "PythonComponent::PythonComponent()" << std::endl;
        }

        PythonComponent::~PythonComponent()
        {
            std::cout << "PythonComponent::~PythonComponent()" << std::endl;

            if (derived != nullptr)
            {
                Py_DECREF(derived);
            }
        }
    }
}