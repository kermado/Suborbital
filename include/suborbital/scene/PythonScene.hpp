#ifndef SUBORBITAL_PYTHON_SCENE_HPP
#define SUBORBITAL_PYTHON_SCENE_HPP

#include <iostream>

#include <Python/Python.h>

#include <suborbital/scene/Scene.hpp>

namespace suborbital
{
    /**
     * The base class for Python defined scenes.
     *
     * Python defined scene classes must derive from this class in order for their members to be accessible from Python
     * scripts.
     */
    class PythonScene : public Scene
    {
    public:
        /**
         * Destructor.
         *
         * Decrements the reference count of the derived Python instance being wrapped.
         */
        virtual ~PythonScene();

        /**
         * Sets the derived Python instance that is being wrapped.
         *
         * This function increments the reference count of the passed `derived_instance`.
         *
         * @param derived_instance Pointer to the derived Python instance.
         */
        void instance(PyObject* derived_instance);

        /**
         * Accessor for the derived Python instance that has been wrapped.
         *
         * @return Derived Python instance.
         */
        PyObject* instance() const;

    protected:
        /**
         * Constructor.
         */
        PythonScene();

    private:
        /**
         * The Python object that was created when constructing classes that derive from this class.
         */
        PyObject* m_instance;
    };
}

#endif
