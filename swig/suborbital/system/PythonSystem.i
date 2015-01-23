%{
    #include <suborbital/system/PythonSystem.hpp>
%}

%feature("director") suborbital::PythonSystem;

%ignore suborbital::PythonSystem::instance();
%ignore suborbital::PythonSystem::instance(PyObject*);

%include <suborbital/system/PythonSystem.hpp>