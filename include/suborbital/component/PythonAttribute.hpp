#ifndef SUBORBITAL_PYTHON_ATTRIBUTE_HPP
#define SUBORBITAL_PYTHON_ATTRIBUTE_HPP

#include <Python/Python.h>

#include <suborbital/component/Attribute.hpp>

namespace suborbital
{
    /**
     * The base class for Python defined attributes that can be attached to entities.
     *
     * Python defined attribute classes must derive from this class in order for their members to be accessible from
     * python scripts.
     */
    class PythonAttribute : public Attribute
    {
    public:
        /**
         * Destructor.
         */
        virtual ~PythonAttribute();

        /**
         * The Python object that was created when constructing Python attribute classes that derive from this class.
         *
         * You really don't want to touch this!
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