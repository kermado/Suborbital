#ifndef SUBORBITAL_PYTHON_BEHAVIOUR_HPP
#define SUBORBITAL_PYTHON_BEHAVIOUR_HPP

#include <Python/Python.h>

#include <suborbital/component/Behaviour.hpp>

namespace suborbital
{
    class PythonBehaviour : public Behaviour
    {
    public:
        /**
         * Destructor.
         */
        virtual ~PythonBehaviour();

        /**
         * The Python object that was created when constructing Python behaviour classes that derive from this
         * class.
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