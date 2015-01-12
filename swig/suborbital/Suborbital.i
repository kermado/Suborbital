%module(directors="1") suborbital

%{
    #include <memory>
%}

// Exception handling.
%feature("director:except") {
    if ($error != NULL) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);
        PyErr_Restore(ptype, pvalue, ptraceback);
        PyErr_Print();
        Py_Exit(1);
    }
}

// Include parts of the c++ standard library.
%include <std_string.i>
%include <std_shared_ptr.i>

// Include WatchPtr smart pointer class.
%include <suborbital/WatchPtr.i>

// Specify which classes should be wrapped using std::shared_ptr.
// Note that this must be done before before any usage or declaration of the classes.
%shared_ptr(suborbital::Event);
%shared_ptr(suborbital::PythonEvent);

// Include classes.
%include <suborbital/Watchable.i>
%include <suborbital/Entity.i>

%include <suborbital/scene/Scene.i>
%include <suborbital/scene/PythonScene.i>

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

// Specify which classes can be wrapped using WatchPtr.
%template(EntityWatchPtr) suborbital::WatchPtr<suborbital::Entity>;
%template(ComponentWatchPtr) suborbital::WatchPtr<suborbital::Component>;
%template(AttributeWatchPtr) suborbital::WatchPtr<suborbital::Attribute>;
%template(PythonAttributeWatchPtr) suborbital::WatchPtr<suborbital::PythonAttribute>;
%template(BehaviourWatchPtr) suborbital::WatchPtr<suborbital::Behaviour>;
%template(ExampleAttributeWatchPtr) suborbital::WatchPtr<suborbital::ExampleAttribute>;