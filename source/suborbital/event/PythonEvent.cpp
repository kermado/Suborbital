#include <iostream>

#include <suborbital/event/PythonEvent.hpp>

namespace suborbital
{
    PythonEvent::PythonEvent()
    : Event()
    , m_instance(nullptr)
    {
        std::cout << "PythonEvent::PythonEvent()" << std::endl;
    }

    PythonEvent::~PythonEvent()
    {
        std::cout << "PythonEvent::~PythonEvent()" << std::endl;
    }

    void PythonEvent::instance(PyObject* derived_instance)
    {
        m_instance = derived_instance;
    }

    PyObject* PythonEvent::instance() const
    {
        return m_instance;
    }
}