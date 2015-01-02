#include <iostream>

#include <suborbital/component/PythonBehaviour.hpp>

namespace suborbital
{
    PythonBehaviour::PythonBehaviour()
    : Behaviour()
    , derived(nullptr)
    {
        std::cout << "PythonBehaviour::PythonBehaviour()" << std::endl;
    }

    PythonBehaviour::~PythonBehaviour()
    {
        std::cout << "PythonBehaviour::~PythonBehaviour()" << std::endl;
        //std::cout << "BEFORE DECREF: " << derived->ob_refcnt << std::endl;
        Py_XDECREF(derived);
        //std::cout << "AFTER DECREF: " << derived->ob_refcnt << std::endl;
    }
}