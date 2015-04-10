%{
    #include <suborbital/EntityManager.hpp>
%}

%feature("shadow") suborbital::EntityManager::all %{
    @property
    def all(self):
        return $action(self)
%}

%include <suborbital/EntityManager.hpp>