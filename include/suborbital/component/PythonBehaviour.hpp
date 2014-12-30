#ifndef SUBORBITAL_PYTHON_BEHAVIOUR_HPP
#define SUBORBITAL_PYTHON_BEHAVIOUR_HPP

#include <suborbital/PythonObject.hpp>
#include <suborbital/component/Behaviour.hpp>

namespace suborbital
{
    /**
     * The base class for Python defined behaviours that can be attached to entities.
     *
     * Python defined behaviour classes must derive from this class in order for their members to be accessible from
     * python scripts.
     */
    class PythonBehaviour : public PythonObject, public Behaviour
    {
    public:
        /**
         * Destructor.
         */
        virtual ~PythonBehaviour();

    protected:
        /**
         * Constructor.
         */
        PythonBehaviour();
    };
}

#endif