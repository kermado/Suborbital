/**
 * Import helper file for the Suborbital module.
 *
 * You should %include this file inside of any third-party modules that need to know about Suborbital types. This is
 * typically used when exposing c++ defined components to Python.
 */

%{
    #include <suborbital/Entity.hpp>
    #include <suborbital/EntityManager.hpp>
    #include <suborbital/EntitySet.hpp>
    #include <suborbital/Watchable.hpp>
    #include <suborbital/WatchPtr.hpp>

    #include <suborbital/component/Attribute.hpp>
    #include <suborbital/component/Behaviour.hpp>
    #include <suborbital/component/Component.hpp>
    #include <suborbital/component/PythonAttribute.hpp>
    #include <suborbital/component/PythonBehaviour.hpp>

    #include <suborbital/event/Event.hpp>
    #include <suborbital/event/EventCallback.hpp>
    #include <suborbital/event/EventCallbackBase.hpp>
    #include <suborbital/event/EventDispatcher.hpp>
    #include <suborbital/event/EventSubscription.hpp>
    #include <suborbital/event/PythonEvent.hpp>
    #include <suborbital/event/PythonEventCallback.hpp>

    #include <suborbital/scene/Scene.hpp>
    #include <suborbital/scene/PythonScene.hpp>

    #include <suborbital/system/System.hpp>
    #include <suborbital/system/PythonSystem.hpp>
%}

%import <suborbital/Module.i>