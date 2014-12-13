%{
    #include <suborbital/Entity.hpp>
    #include <suborbital/component/PythonComponent.hpp>
%}

# Convert components to the type specified by the class name.
# Thanks to Flexo:
# http://stackoverflow.com/questions/27392602/swig-downcasting-from-base-to-derived/27417168#27417168
# http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
%typemap(out) suborbital::component::Component* suborbital::Entity::create_component
{
    const suborbital::component::PythonComponent* const python_component = dynamic_cast<suborbital::component::PythonComponent*>($1);
    if (python_component)
    {
        $result = python_component->derived;
    }
    else
    {
        const std::string lookup_typename = "suborbital::component::" + *arg2 + "*";
        swig_type_info* const out_type = SWIG_TypeQuery(lookup_typename.c_str());
        $result = SWIG_NewPointerObj(SWIG_as_voidptr($1), out_type, $owner);
    }
}

# Convert components to the type specified by the class name.
# Thanks to Flexo:
# http://stackoverflow.com/questions/27392602/swig-downcasting-from-base-to-derived/27417168#27417168
# http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
%typemap(out) suborbital::component::Component* suborbital::Entity::component
{
    const suborbital::component::PythonComponent* const python_component = dynamic_cast<suborbital::component::PythonComponent*>($1);
    if (python_component)
    {
        $result = python_component->derived;
    }
    else
    {
        const std::string lookup_typename = "suborbital::component::" + *arg2 + "*";
        swig_type_info* const out_type = SWIG_TypeQuery(lookup_typename.c_str());
        $result = SWIG_NewPointerObj(SWIG_as_voidptr($1), out_type, $owner);
    }
}

%include <suborbital/Entity.hpp>