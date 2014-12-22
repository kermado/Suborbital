%{
    #include <suborbital/component/PythonBehaviour.hpp>
%}

%feature("director") suborbital::PythonBehaviour;

%ignore suborbital::PythonBehaviour::derived;

%include <suborbital/component/PythonBehaviour.hpp>