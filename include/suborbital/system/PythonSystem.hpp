#ifndef SUBORBITAL_PYTHON_SYSTEM_HPP
#define SUBORBITAL_PYTHON_SYSTEM_HPP

#include <Python/Python.h>

#include <suborbital/system/System.hpp>

namespace suborbital
{
    /**
     * The base class for Python defined systems that that process entities in a scene.
     *
     * Python defined systems classes must derive from this class in order for their members to be accessible from
     * Python scripts.
     */
    class PythonSystem : public System
    {
    public:
        /**
         * Destructor.
         *
         * Decrements the reference count of the derived Python instance being wrapped.
         */
        virtual ~PythonSystem();

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
        PythonSystem();

    private:
        /**
         * The Python object that was created when constructing classes that derive from this class.
         */
        PyObject* m_instance;
    };
}

#endif