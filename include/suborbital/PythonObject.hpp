#ifndef PYTHON_OBJECT_HPP
#define PYTHON_OBJECT_HPP

#include <Python/Python.h>

namespace suborbital
{
    class PythonObject
    {
    public:
        /**
         * Destructor.
         */
        virtual ~PythonObject();

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
        PythonObject();
    };
}

#endif