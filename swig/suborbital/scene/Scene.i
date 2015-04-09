%{
    #include <suborbital/scene/Scene.hpp>
%}

%feature("director") suborbital::Scene;

// Custom implementation for the Python method that calls the `create_system function`. This method takes a Python type
// as its only parameter and passes the name of the provided type into the `create_system` function as a string. This is
// done to ensure that the provided type is imported (which would not be possible if just a type name was to be provided
// by the user).
%feature("shadow") suborbital::Scene::create_system %{
    def create_system(self, system_type):
        return $action(self, system_type.__name__)
%}

// Custom implementation for the Python method that calls the `system function`. This method takes a Python type as its
// only parameter and passes the name of the provided type into the `system` function as a string. This is done to
// ensure that the provided type is imported (which would not be possible if just a type name was to be provided by the
// user).
%feature("shadow") suborbital::Scene::system %{
    def system(self, system_type):
        return $action(self, system_type.__name__)
%}

%include <suborbital/scene/Scene.hpp>