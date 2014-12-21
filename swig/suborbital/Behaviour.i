%{
    #include <suborbital/Behaviour.hpp>
%}

%feature("director") suborbital::Behaviour;

%ignore suborbital::create_behaviour(const std::string&);

%include <suborbital/Behaviour.hpp>