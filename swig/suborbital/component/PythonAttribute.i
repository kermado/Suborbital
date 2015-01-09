%{
    #include <suborbital/component/PythonAttribute.hpp>
%}

%feature("director") suborbital::PythonAttribute;

%ignore suborbital::PythonAttribute::instance();
%ignore suborbital::PythonAttribute::instance(PyObject*);

%include <suborbital/component/PythonAttribute.hpp>