%{
    #include <suborbital/watch_ptr.hpp>
    #include <suborbital/Entity.hpp>
    #include <suborbital/component/PythonAttribute.hpp>
    #include <suborbital/event/PythonEvent.hpp>
    #include <suborbital/event/EventSubscription.hpp>
    #include <suborbital/event/EventCallbackBase.hpp>
    #include <suborbital/event/PythonEventCallback.hpp>
%}

// Convert attributes to the type specified by the class name.
//
// Thanks to Flexo:
// http://stackoverflow.com/questions/27392602/swig-downcasting-from-base-to-derived/27417168#27417168
// http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
%typemap(out) suborbital::watch_ptr<suborbital::Attribute> suborbital::Entity::create_attribute
{
    suborbital::watch_ptr<suborbital::PythonAttribute> python_attribute = suborbital::dynamic_pointer_cast<suborbital::PythonAttribute>($1);
    if (python_attribute)
    {
        $result = python_attribute->instance();
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

// Convert attributes to the type specified by the class name.
//
// Thanks to Flexo:
// http://stackoverflow.com/questions/27392602/swig-downcasting-from-base-to-derived/27417168#27417168
// http://stackoverflow.com/questions/27454289/retrieving-a-python-type-back-from-c/27454946#27454946
%typemap(out) suborbital::watch_ptr<suborbital::Attribute> suborbital::Entity::attribute
{
    suborbital::watch_ptr<suborbital::PythonAttribute> python_attribute = suborbital::dynamic_pointer_cast<suborbital::PythonAttribute>($1);
    if (python_attribute)
    {
        $result = python_attribute->instance();
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

// Define a WeaklyBoundMethod class that wraps a method bound to a weakref of an object. This is required for callback
// functions so as to avoid increasing the reference count of the object that subscribes for an event.
%pythoncode %{
class WeaklyBoundMethod:
    def __init__(self, meth):
        self._self = weakref.ref(meth.__self__)
        self._func = meth.__func__

    def __call__(self, *args, **kw):
        _self = self._self()
        if _self is None:
            raise weakref.ReferenceError()
        return self._func(_self, *args, **kw)
%}

// Manually define the Python wrapper function for Entity::subscribe so that we convert the callback function from a
// strongly bound method to weakly bound method, using the WeaklyBoundMethod class defined above.
%feature("shadow") suborbital::Entity::subscribe(const std::string&, PyObject*) %{
    def subscribe(self, event_name, strongly_bound_method):
        return $action(self, event_name, WeaklyBoundMethod(strongly_bound_method))
%}

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

// Ignore the Entity::publish, Entity::broadcast_descendents and Entity::broadcast functions. Alternative
// implementations of these functions are provided below.
%ignore suborbital::Entity::publish(const std::string&, std::shared_ptr<suborbital::Event>);
%ignore suborbital::Entity::broadcast_descendents(const std::string&, std::shared_ptr<suborbital::Event>);
%ignore suborbital::Entity::broadcast(const std::string&, std::shared_ptr<suborbital::Event>);

// Our alternative implementation of the Entity::publish function stores the PyObject* for the derived event inside of
// the PythonEvent instance. This allows us to pass the PyObject* to the Python callback function, thus preserving type
// information.
%extend suborbital::Entity
{
    void suborbital::Entity::publish(const std::string& event_name, PyObject* python_type)
    {
        void* result = NULL;
        const int status = SWIG_ConvertPtr(python_type, &result, SWIGTYPE_p_std__shared_ptrT_suborbital__PythonEvent_t, 0);
        assert(SWIG_IsOK(status));

        std::shared_ptr<suborbital::PythonEvent> event = *(reinterpret_cast<std::shared_ptr<suborbital::PythonEvent>*>(result));
        event->instance(python_type);
        $self->publish(event_name, event);
    }

    void suborbital::Entity::broadcast_descendents(const std::string& event_name, PyObject* python_type)
    {
        void* result = NULL;
        const int status = SWIG_ConvertPtr(python_type, &result, SWIGTYPE_p_std__shared_ptrT_suborbital__PythonEvent_t, 0);
        assert(SWIG_IsOK(status));

        std::shared_ptr<suborbital::PythonEvent> event = *(reinterpret_cast<std::shared_ptr<suborbital::PythonEvent>*>(result));
        event->instance(python_type);
        $self->broadcast_descendents(event_name, event);
    }

    void suborbital::Entity::broadcast(const std::string& event_name, PyObject* python_type)
    {
        void* result = NULL;
        const int status = SWIG_ConvertPtr(python_type, &result, SWIGTYPE_p_std__shared_ptrT_suborbital__PythonEvent_t, 0);
        assert(SWIG_IsOK(status));

        std::shared_ptr<suborbital::PythonEvent> event = *(reinterpret_cast<std::shared_ptr<suborbital::PythonEvent>*>(result));
        event->instance(python_type);
        $self->broadcast(event_name, event);
    }
}

// Now expose the Entity class.
%include <suborbital/Entity.hpp>