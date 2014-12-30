#include <iostream>

#include <suborbital/component/PythonBehaviour.hpp>

namespace suborbital
{
    PythonBehaviour::PythonBehaviour()
    : PythonObject()
    , Behaviour()
    {
        std::cout << "PythonBehaviour::PythonBehaviour()" << std::endl;
    }

    PythonBehaviour::~PythonBehaviour()
    {
        std::cout << "PythonBehaviour::PythonBehaviour()" << std::endl;
    }
}