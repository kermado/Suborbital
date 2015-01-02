%{
    #include <suborbital/component/Component.hpp>
%}

%feature("director") suborbital::Component;

%feature("shadow") suborbital::Component::entity %{
    @property
    def entity(self):
        return $action(self)
%}

%include <suborbital/component/Component.hpp>