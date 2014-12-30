%module(directors="1") suborbital

%{
    #include <memory>
%}

// Include parts of the c++ standard library.
%include <std_string.i>
%include <std_shared_ptr.i>

// Include watch_ptr smart pointer class.
%include <suborbital/watch_ptr.i>

// Specify which classes should be wrapped using std::shared_ptr.
// Note that this must be done before before any usage or declaration of the classes.
%shared_ptr(suborbital::Event);
%shared_ptr(suborbital::PythonEvent);

// Include classes.
%include <suborbital/PythonObject.i>
%include <suborbital/Watchable.i>
%include <suborbital/Entity.i>
%include <suborbital/component/Component.i>
%include <suborbital/component/Attribute.i>
%include <suborbital/component/Behaviour.i>
%include <suborbital/component/PythonAttribute.i>
%include <suborbital/component/PythonBehaviour.i>
%include <suborbital/component/ExampleAttribute.i>
%include <suborbital/event/Event.i>
%include <suborbital/event/PythonEvent.i>
%include <suborbital/event/EventSubscription.i>
%include <suborbital/event/EventCallbackBase.i>
%include <suborbital/event/PythonEventCallback.i>

// Specify which classes can be wrapped using watch_ptr.
%template(EntityWatchPtr) suborbital::watch_ptr<suborbital::Entity>;
%template(ComponentWatchPtr) suborbital::watch_ptr<suborbital::Component>;
%template(AttributeWatchPtr) suborbital::watch_ptr<suborbital::Attribute>;
%template(PythonAttributeWatchPtr) suborbital::watch_ptr<suborbital::PythonAttribute>;
%template(BehaviourWatchPtr) suborbital::watch_ptr<suborbital::Behaviour>;
%template(ExampleAttributeWatchPtr) suborbital::watch_ptr<suborbital::ExampleAttribute>;