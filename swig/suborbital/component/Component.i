%{
    #include <suborbital/component/Component.hpp>
%}

%feature("director") suborbital::component::Component;

%ignore suborbital::component::create(const std::string&);

%include <suborbital/component/Component.hpp>