%{
    #include <suborbital/component/PythonAttribute.hpp>
%}

%feature("director") suborbital::PythonAttribute;

%ignore suborbital::PythonAttribute::derived;

%include <suborbital/component/PythonAttribute.hpp>