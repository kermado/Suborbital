%{
    #include <suborbital/component/PythonComponent.hpp>
%}

%feature("director") suborbital::component::PythonComponent;

%ignore suborbital::component::PythonComponent::derived;

%include <suborbital/component/PythonComponent.hpp>