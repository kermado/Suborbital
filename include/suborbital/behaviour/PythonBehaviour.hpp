#ifndef PYTHONbehaviour_HPP
#define PYTHONbehaviour_HPP

#include <suborbital/behaviour/Behaviour.hpp>

namespace suborbital
{
    namespace behaviour
    {
        class PythonBehaviour : public Behaviour
        {
        public:
            /**
             * Constructor.
             */
            PythonBehaviour();

            /**
             * Destructor.
             */
            virtual ~PythonBehaviour();

            /**
             * The Python object that was created when constructing Python behaviour classes that derive from this
             * class.
             */
            PyObject* derived;
        };
    }
}

#endif