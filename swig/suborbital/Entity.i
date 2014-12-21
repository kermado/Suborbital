%{
    #include <suborbital/Entity.hpp>
    #include <suborbital/PythonBehaviour.hpp>
%}

# Convert behaviours to the type specified by the class name.
# Thanks to Flexo:
# http://stackoverflow.com/questions/27392602/swig-downcasting-from-base-to-derived/27417168#27417168
# http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
%typemap(out) suborbital::Behaviour* suborbital::Entity::create_behaviour
{
    const suborbital::PythonBehaviour* const python_behaviour = dynamic_cast<suborbital::PythonBehaviour*>($1);
    if (python_behaviour)
    {
        $result = python_behaviour->derived;
    }
    else
    {
        const std::string lookup_typename = "suborbital::" + *arg2 + "*";
        swig_type_info* const out_type = SWIG_TypeQuery(lookup_typename.c_str());
        $result = SWIG_NewPointerObj(SWIG_as_voidptr($1), out_type, $owner);
    }
}

# Convert behaviours to the type specified by the class name.
# Thanks to Flexo:
# http://stackoverflow.com/questions/27392602/swig-downcasting-from-base-to-derived/27417168#27417168
# http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
%typemap(out) suborbital::Behaviour* suborbital::Entity::behaviour
{
    const suborbital::PythonBehaviour* const python_behaviour = dynamic_cast<suborbital::PythonBehaviour*>($1);
    if (python_behaviour)
    {
        $result = python_behaviour->derived;
    }
    else
    {
        const std::string lookup_typename = "suborbital::" + *arg2 + "*";
        swig_type_info* const out_type = SWIG_TypeQuery(lookup_typename.c_str());
        $result = SWIG_NewPointerObj(SWIG_as_voidptr($1), out_type, $owner);
    }
}

%include <suborbital/Entity.hpp>