%module(directors="1") suborbital

%{
    #include <memory>
%}

// Include parts of the c++ standard library.
%include <std_string.i>
%include <std_shared_ptr.i>

// Specify which classes can be wrapped using std::shared_ptr.
// Note that these must be specified before including classes.
%shared_ptr(suborbital::Entity)

// Include classes.
%include <suborbital/Entity.i>
%include <suborbital/Component.i>
%include <suborbital/Behaviour.i>
%include <suborbital/PythonBehaviour.i>
