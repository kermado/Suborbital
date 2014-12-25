%feature("director") suborbital::Entity;

%{
    #include <suborbital/watch_ptr.hpp>
    #include <suborbital/Entity.hpp>
    #include <suborbital/component/PythonAttribute.hpp>

    using namespace suborbital;
%}

# Convert attributes to the type specified by the class name.
#
# Thanks to Flexo:
# http://stackoverflow.com/questions/27392602/swig-downcasting-from-base-to-derived/27417168#27417168
# http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
%typemap(out) watch_ptr<Attribute> Entity::create_attribute
{
    watch_ptr<PythonAttribute> python_attribute = dynamic_pointer_cast<PythonAttribute>($1);
    if (python_attribute)
    {
        $result = python_attribute->derived;
        Py_INCREF($result);
    }
    else
    {
        const std::string lookup_typename = "suborbital::watch_ptr<suborbital::" + *arg2 + ">";
        swig_type_info* const out_type = SWIG_TypeQuery(lookup_typename.c_str());
        assert(out_type != NULL);
        $result = SWIG_NewPointerObj(SWIG_as_voidptr($1.get()), out_type, $owner);
    }
}

# Convert attributes to the type specified by the class name.
#
# Thanks to Flexo:
# http://stackoverflow.com/questions/27392602/swig-downcasting-from-base-to-derived/27417168#27417168
# http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
%typemap(out) suborbital::watch_ptr<suborbital::Attribute> suborbital::Entity::attribute
{
    watch_ptr<PythonAttribute> python_attribute = dynamic_pointer_cast<PythonAttribute>($1);
    if (python_attribute)
    {
        $result = python_attribute->derived;
        Py_INCREF($result);
    }
    else
    {
        const std::string lookup_typename = "suborbital::watch_ptr<suborbital::" + *arg2 + ">*";
        swig_type_info* const out_type = SWIG_TypeQuery(lookup_typename.c_str());
        assert(out_type != NULL);
        $result = SWIG_NewPointerObj(SWIG_as_voidptr($1.get()), out_type, $owner);
    }
}

%include <suborbital/Entity.hpp>