#include <iostream>
#include <Python.h>

#include <suborbital/behaviour/PythonBehaviour.hpp>

namespace suborbital
{
    namespace behaviour
    {
        PythonBehaviour::PythonBehaviour()
        : Behaviour()
        , derived(nullptr)
        {
            std::cout << "PythonBehaviour::PythonBehaviour()" << std::endl;
        }

        PythonBehaviour::~PythonBehaviour()
        {
            std::cout << "PythonBehaviour::PythonBehaviour()" << std::endl;

            if (derived != nullptr)
            {
                Py_DECREF(derived);
            }
        }
    }
}