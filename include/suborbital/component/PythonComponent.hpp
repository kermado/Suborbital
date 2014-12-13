#ifndef PYTHONCOMPONENT_HPP
#define PYTHONCOMPONENT_HPP

#include <suborbital/component/Component.hpp>

namespace suborbital
{
    namespace component
    {
        class PythonComponent : public Component
        {
        public:
            /**
             * Constructor.
             */
            PythonComponent();

            /**
             * Destructor.
             */
            virtual ~PythonComponent();

            /**
             * The Python object that was created when constructing Python component classes that derive from this
             * class.
             */
            PyObject* derived;
        };
    }
}

#endif