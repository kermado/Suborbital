%{
    #include <suborbital/PythonBehaviour.hpp>
%}

%feature("director") suborbital::PythonBehaviour;

%ignore suborbital::PythonBehaviour::derived;

%include <suborbital/PythonBehaviour.hpp>