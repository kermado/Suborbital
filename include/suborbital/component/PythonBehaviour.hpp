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
     * python scripts.
     */
    class PythonBehaviour : public Behaviour
    {
    public:
        /**
         * Destructor.
         */
        virtual ~PythonBehaviour();

    public:
        /**
         * The Python object that was created when constructing classes that derive from this class.
         *
         * You really don't want to touch this!
         */
        PyObject* derived;

    protected:
        /**
         * Constructor.
         */
        PythonBehaviour();
    };
}

#endif