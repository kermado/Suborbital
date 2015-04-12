#include <cassert>

#include <suborbital/system/PythonSystem.hpp>

namespace suborbital
{
    PythonSystem::PythonSystem()
    : System()
    , m_instance(nullptr)
    {
        // Nothing to do.
    }

    PythonSystem::~PythonSystem()
    {
        Py_XDECREF(m_instance);
    }

    void PythonSystem::instance(PyObject* derived_instance)
    {
        assert(derived_instance != nullptr);

        m_instance = derived_instance;
        Py_XINCREF(derived_instance);
    }

    PyObject* PythonSystem::instance() const
    {
        return m_instance;
    }
}