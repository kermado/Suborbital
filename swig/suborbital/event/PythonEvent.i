%{
    #include <suborbital/event/PythonEvent.hpp>
%}

%feature("director") suborbital::PythonEvent;

%ignore suborbital::PythonEvent::instance();
%ignore suborbital::PythonEvent::instance(PyObject*);

%include <suborbital/event/PythonEvent.hpp>