#include <iostream>
#include <cassert>

#include <suborbital/scene/PythonScene.hpp>

namespace suborbital
{
    PythonScene::PythonScene()
    : Scene()
    , m_instance(nullptr)
    {
        std::cout << "PythonScene::PythonScene()" << std::endl;
    }

    PythonScene::~PythonScene()
    {
        std::cout << "PythonScene::~PythonScene()" << std::endl;

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