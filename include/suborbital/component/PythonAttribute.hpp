#ifndef SUBORBITAL_PYTHON_ATTRIBUTE_HPP
#define SUBORBITAL_PYTHON_ATTRIBUTE_HPP

#include <suborbital/PythonObject.hpp>
#include <suborbital/component/Attribute.hpp>

namespace suborbital
{
    /**
     * The base class for Python defined attributes that can be attached to entities.
     *
     * Python defined attribute classes must derive from this class in order for their members to be accessible from
     * python scripts.
     */
    class PythonAttribute : public PythonObject, public Attribute
    {
    public:
        /**
         * Destructor.
         */
        virtual ~PythonAttribute();

    protected:
        /**
         * Constructor.
         */
        PythonAttribute();
    };
}

#endif