%{
    #include <suborbital/behaviour/Behaviour.hpp>
%}

%feature("director") suborbital::behaviour::Behaviour;

%ignore suborbital::behaviour::create(const std::string&);

%include <suborbital/behaviour/Behaviour.hpp>