#include <iostream>
#include <cassert>

#include <suborbital/component/PythonBehaviour.hpp>

namespace suborbital
{
    PythonBehaviour::PythonBehaviour()
    : Behaviour()
    , m_instance(nullptr)
    {
        std::cout << "PythonBehaviour::PythonBehaviour()" << std::endl;
    }

    PythonBehaviour::~PythonBehaviour()
    {
        std::cout << "PythonBehaviour::~PythonBehaviour()" << std::endl;

        Py_XDECREF(m_instance);
    }

    void PythonBehaviour::instance(PyObject* derived_instance)
    {
        assert(derived_instance != nullptr);

        m_instance = derived_instance;
        Py_XINCREF(derived_instance);
    }

    PyObject* PythonBehaviour::instance() const
    {
        return m_instance;
    }
}