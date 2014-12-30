%{
    #include <suborbital/watch_ptr.hpp>
    #include <suborbital/Entity.hpp>
    #include <suborbital/component/PythonAttribute.hpp>
    #include <suborbital/event/EventSubscription.hpp>
    #include <suborbital/event/EventCallbackBase.hpp>
    #include <suborbital/event/PythonEventCallback.hpp>
%}

# Convert attributes to the type specified by the class name.
#
# Thanks to Flexo:
# http://stackoverflow.com/questions/27392602/swig-downcasting-from-base-to-derived/27417168#27417168
# http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
%typemap(out) suborbital::watch_ptr<suborbital::Attribute> suborbital::Entity::create_attribute
{
    suborbital::watch_ptr<suborbital::PythonAttribute> python_attribute = suborbital::dynamic_pointer_cast<suborbital::PythonAttribute>($1);
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
    suborbital::watch_ptr<suborbital::PythonAttribute> python_attribute = suborbital::dynamic_pointer_cast<suborbital::PythonAttribute>($1);
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

// Ignore the Entity::subscribe function. An alternative implementation is provided below that SWIG is able to work
// with.
%ignore suborbital::Entity::subscribe(const std::string&, std::unique_ptr<suborbital::EventCallbackBase>);

// The scripting language should take ownership of the EventSubscription pointer that is returned by our SWIG specific
// implementation of the Entity::subscribe function.
%newobject suborbital::Entity::subscribe(const std::string&, PyObject*);

// SWIG doesn't have any support for std::unique_ptr, so we need to provide an alternative implementation for the
// Entity::subscribe function that returns a raw pointer instead. Note (as above) that the returned pointer should be
// managed by the scripting language's garbage collector.
%extend suborbital::Entity
{
    suborbital::EventSubscription* suborbital::Entity::subscribe(const std::string& event_name, PyObject* callback)
    {
        std::unique_ptr<suborbital::EventCallbackBase> callback_wrapper(new suborbital::PythonEventCallback(callback));
        std::unique_ptr<suborbital::EventSubscription> subscription = $self->subscribe(event_name, std::move(callback_wrapper));
        return subscription.release();
    }
}

// Now expose the Entity class.
%include <suborbital/Entity.hpp>