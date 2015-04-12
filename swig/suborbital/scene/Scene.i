%{
    #include <suborbital/scene/Scene.hpp>
%}

%feature("director") suborbital::Scene;

// Rewrite getter methods to use Python properties.
%feature("shadow") suborbital::Scene::entities %{
    @property
    def entities(self):
        return $action(self)
%}

%feature("shadow") suborbital::Scene::has_camera %{
    @property
    def has_camera(self):
        return $action(self)
%}

%feature("shadow") suborbital::Scene::camera %{
    @property
    def camera(self):
        return $action(self)

    @camera.setter
    def camera(self, value):
        return $action(self, value)
%}

// Add simplified methods that use the event's class name as the event name.
%feature("shadow") suborbital::Scene::publish %{
    def publish(self, event_name, event):
            return $action(self, event_name, event)

    def publish(self, event):
        return $action(self, type(event).__name__, event)
%}

%feature("shadow") suborbital::Scene::broadcast %{
    def broadcast(self, event_name, event):
            return $action(self, event_name, event)

    def broadcast(self, event):
        return $action(self, type(event).__name__, event)
%}

%feature("shadow") suborbital::Scene::subscribe %{
    def subscribe(self, event, callback):
        if isinstance(event, str):
            return $action(self, event, callback)
        else:
            return $action(self, event.__name__, callback)
%}

// Manually define the Python wrapper function for Scene::subscribe so that we convert the callback function from a
// strongly bound method to weakly bound method, using the WeaklyBoundMethod class defined above.
%feature("shadow") suborbital::Scene::subscribe(const std::string&, PyObject*) %{
    def subscribe(self, event, strongly_bound_method):
        if isinstance(event, str):
            return $action(self, event, WeaklyBoundMethod(strongly_bound_method))
        else:
            return $action(self, event.__name__, WeaklyBoundMethod(strongly_bound_method))
%}

// Ignore the Scene::subscribe function. An alternative implementation is provided below that SWIG is able to work with.
%ignore suborbital::Scene::subscribe(const std::string&, std::unique_ptr<suborbital::EventCallbackBase>);

// The scripting language should take ownership of the EventSubscription pointer that is returned by our SWIG specific
// implementation of the Scene::subscribe function.
%newobject suborbital::Scene::subscribe(const std::string&, PyObject*);

// SWIG doesn't have any support for std::unique_ptr, so we need to provide an alternative implementation for the
// Scene::subscribe function that returns a raw pointer instead. Note (as above) that the returned pointer should be
// managed by the scripting language's garbage collector.
%extend suborbital::Scene
{
    suborbital::EventSubscription* suborbital::Scene::subscribe(const std::string& event_name, PyObject* callback)
    {
        std::unique_ptr<suborbital::EventCallbackBase> callback_wrapper(new suborbital::PythonEventCallback(callback));
        std::unique_ptr<suborbital::EventSubscription> subscription = $self->subscribe(event_name, std::move(callback_wrapper));
        return subscription.release();
    }
}

// Ignore the Scene::publish and Scene::broadcast functions. Alternative implementations of these functions are provided
// below.
%ignore suborbital::Scene::publish(const std::string&, std::shared_ptr<suborbital::Event>);
%ignore suborbital::Scene::broadcast_descendents(const std::string&, std::shared_ptr<suborbital::Event>);
%ignore suborbital::Scene::broadcast(const std::string&, std::shared_ptr<suborbital::Event>);

// Our alternative implementation of the Scene::publish function stores the PyObject* for the derived event inside of
// the PythonEvent instance. This allows us to pass the PyObject* to the Python callback function, thus preserving type
// information.
%extend suborbital::Scene
{
    void suborbital::Scene::publish(const std::string& event_name, PyObject* python_type)
    {
        void* result = NULL;
        const int status = SWIG_ConvertPtr(python_type, &result, SWIGTYPE_p_std__shared_ptrT_suborbital__PythonEvent_t, 0);
        assert(SWIG_IsOK(status));

        std::shared_ptr<suborbital::PythonEvent> event = *(reinterpret_cast<std::shared_ptr<suborbital::PythonEvent>*>(result));
        event->instance(python_type);
        $self->publish(event_name, event);
    }

    void suborbital::Scene::broadcast(const std::string& event_name, PyObject* python_type)
    {
        void* result = NULL;
        const int status = SWIG_ConvertPtr(python_type, &result, SWIGTYPE_p_std__shared_ptrT_suborbital__PythonEvent_t, 0);
        assert(SWIG_IsOK(status));

        std::shared_ptr<suborbital::PythonEvent> event = *(reinterpret_cast<std::shared_ptr<suborbital::PythonEvent>*>(result));
        event->instance(python_type);
        $self->broadcast(event_name, event);
    }
}

// Custom implementation for the Python method that calls the `create_system function`. This method takes a Python type
// as its only parameter and passes the name of the provided type into the `create_system` function as a string. This is
// done to ensure that the provided type is imported (which would not be possible if just a type name was to be provided
// by the user).
%feature("shadow") suborbital::Scene::create_system %{
    def create_system(self, system_type):
        return $action(self, system_type.__name__)
%}

// Custom implementation for the Python method that calls the `system function`. This method takes a Python type as its
// only parameter and passes the name of the provided type into the `system` function as a string. This is done to
// ensure that the provided type is imported (which would not be possible if just a type name was to be provided by the
// user).
%feature("shadow") suborbital::Scene::system %{
    def system(self, system_type):
        return $action(self, system_type.__name__)
%}

%include <suborbital/scene/Scene.hpp>