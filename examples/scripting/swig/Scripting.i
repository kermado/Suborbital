%module scripting

// Include the Suborbital SWIG module.
%include <suborbital/Suborbital.i>

// Include classes.
%include "ExampleAttribute.i"

// Specify which classes can be wrapped using WatchPtr.
%template(ExampleAttributeWatchPtr) suborbital::WatchPtr<ExampleAttribute>;