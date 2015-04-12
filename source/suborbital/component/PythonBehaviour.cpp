#include <suborbital/component/PythonBehaviour.hpp>

namespace suborbital
{
    PythonBehaviour::PythonBehaviour()
    : Behaviour()
    , m_instance(nullptr)
    {
        // Nothing to do.
    }

    PythonBehaviour::~PythonBehaviour()
    {
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