#ifndef SUBORBITAL_PYTHON_BEHAVIOUR_HPP
#define SUBORBITAL_PYTHON_BEHAVIOUR_HPP

#include <Python/Python.h>

#include <suborbital/component/Behaviour.hpp>

namespace suborbital
{
    /**
     * The base class for Python defined behaviours that can be attached to entities.
     *
     * Python defined behaviour classes must derive from this class in order for their members to be accessible from
     * Python scripts.
     */
    class PythonBehaviour : public Behaviour
    {
    public:
        /**
         * Destructor.
         *
         * Decrements the reference count of the derived Python instance being wrapped.
         */
        virtual ~PythonBehaviour();

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
        PythonBehaviour();

    private:
        /**
         * The Python object that was created when constructing classes that derive from this class.
         */
        PyObject* m_instance;
    };
}

#endif