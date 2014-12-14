%{
    #include <suborbital/behaviour/PythonBehaviour.hpp>
%}

%feature("director") suborbital::behaviour::PythonBehaviour;

%ignore suborbital::behaviour::PythonBehaviour::derived;

%include <suborbital/behaviour/PythonBehaviour.hpp>