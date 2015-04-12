#include <cassert>

#include <suborbital/scene/PythonScene.hpp>

namespace suborbital
{
    PythonScene::PythonScene()
    : Scene()
    , m_instance(nullptr)
    {
        // Nothing to do.
    }

    PythonScene::~PythonScene()
    {
        Py_XDECREF(m_instance);
    }

    void PythonScene::instance(PyObject* derived_instance)
    {
        assert(derived_instance != nullptr);
        m_instance = derived_instance;
        Py_XINCREF(derived_instance);
    }

    PyObject* PythonScene::instance() const
    {
        return m_instance;
    }
}