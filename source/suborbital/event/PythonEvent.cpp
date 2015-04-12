#include <suborbital/event/PythonEvent.hpp>

namespace suborbital
{
    PythonEvent::PythonEvent()
    : Event()
    , m_instance(nullptr)
    {
        // Nothing to do.
    }

    PythonEvent::~PythonEvent()
    {
        // Nothing to do.
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