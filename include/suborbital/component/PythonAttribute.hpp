#ifndef SUBORBITAL_PYTHON_ATTRIBUTE_HPP
#define SUBORBITAL_PYTHON_ATTRIBUTE_HPP

#include <Python/Python.h>

#include <suborbital/component/Attribute.hpp>

namespace suborbital
{
    class PythonAttribute : public Attribute
    {
    public:
        /**
         * Destructor.
         */
        virtual ~PythonAttribute();

        /**
         * The Python object that was created when constructing Python attribute classes that derive from this class.
         */
        PyObject* derived;

    protected:
        /**
         * Constructor.
         */
        PythonAttribute();
    };
}

#endif