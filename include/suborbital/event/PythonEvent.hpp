#ifndef SUBORBITAL_PYTHON_EVENT_HPP
#define SUBORBITAL_PYTHON_EVENT_HPP

#include <Python/Python.h>

#include <suborbital/event/Event.hpp>

namespace suborbital
{
    class PythonEvent : public Event
    {
    public:
        /**
         * Destructor.
         */
        virtual ~PythonEvent();

        /**
         * Sets the derived Python instance that is being wrapped.
         *
         * This function does NOT increment the reference count of the passed `derived_instance`, unlike other Python
         * wrapper classes. The reason for this is that events are wrapped by shared_ptr's and so SWIG automatically
         * manages the reference counting for us.
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
        PythonEvent();

    private:
        /**
         * The Python object that was created when constructing classes that derive from this class.
         */
        PyObject* m_instance;
    };
}

#endif