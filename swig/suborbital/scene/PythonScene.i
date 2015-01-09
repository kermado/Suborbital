%{
    #include <suborbital/scene/PythonScene.hpp>
%}

%feature("director") suborbital::PythonScene;

%ignore suborbital::PythonScene::instance();
%ignore suborbital::PythonScene::instance(PyObject*);

%include <suborbital/scene/PythonScene.hpp>