#include <iostream>
#include <cassert>

#include <suborbital/component/PythonAttribute.hpp>

namespace suborbital
{
    PythonAttribute::PythonAttribute()
    : Attribute()
    , m_instance(nullptr)
    {
        std::cout << "PythonAttribute::PythonAttribute()" << std::endl;
    }

    PythonAttribute::~PythonAttribute()
    {
        std::cout << "PythonAttribute::~PythonAttribute()" << std::endl;

        Py_XDECREF(m_instance);
    }

    void PythonAttribute::instance(PyObject* derived_instance)
    {
        assert(derived_instance != nullptr);

        m_instance = derived_instance;
        Py_XINCREF(derived_instance);
    }

    PyObject* PythonAttribute::instance() const
    {
        return m_instance;
    }
}