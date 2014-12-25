%module(directors="1") suborbital

%{
    #include <memory>
%}

// Include parts of the c++ standard library.
%include <std_string.i>

// Include watch_ptr smart pointer class.
%include <suborbital/watch_ptr.i>

// Specify which classes can be wrapped using watch_ptr.
// Note that these must be specified before including classes.
%template(ComponentWatchPtr) suborbital::watch_ptr<suborbital::Component>;
%template(AttributeWatchPtr) suborbital::watch_ptr<suborbital::Attribute>;
%template(PythonAttributeWatchPtr) suborbital::watch_ptr<suborbital::PythonAttribute>;
%template(BehaviourWatchPtr) suborbital::watch_ptr<suborbital::Behaviour>;
%template(ExampleAttributeWatchPtr) suborbital::watch_ptr<suborbital::ExampleAttribute>;

// Include classes.
%include <suborbital/Watchable.i>
%include <suborbital/Entity.i>
%include <suborbital/component/Component.i>
%include <suborbital/component/Attribute.i>
%include <suborbital/component/Behaviour.i>
%include <suborbital/component/PythonAttribute.i>
%include <suborbital/component/PythonBehaviour.i>
%include <suborbital/component/ExampleAttribute.i>
