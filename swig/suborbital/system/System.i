%{
    #include <suborbital/system/System.hpp>
%}

%feature("director") suborbital::System;

// Rewrite getter methods to use Python properties.
%feature("shadow") suborbital::System::scene %{
    @property
    def scene(self):
        return $action(self)
%}

%include <suborbital/system/System.hpp>