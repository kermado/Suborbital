%{
    #include <suborbital/component/PythonBehaviour.hpp>
%}

%feature("director") suborbital::PythonBehaviour;

%ignore suborbital::PythonBehaviour::instance();
%ignore suborbital::PythonBehaviour::instance(PyObject*);

%include <suborbital/component/PythonBehaviour.hpp>