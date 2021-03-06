#ifndef SUBORBITAL_SCENE_HPP
#define SUBORBITAL_SCENE_HPP

#include <cassert>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

#include <suborbital/Watchable.hpp>
#include <suborbital/WatchPtr.hpp>
#include <suborbital/NonCopyable.hpp>
#include <suborbital/EntityManager.hpp>

#include <suborbital/event/EventDispatcher.hpp>

#include <suborbital/system/System.hpp>
#include <suborbital/system/SystemRegistry.hpp>

namespace suborbital
{
    // Forward declarations.
    class SceneStack;
    class Entity;
    class Event;

    class Scene : public Watchable, private NonCopyable
    {
    friend SceneStack;
    public:
        /**
         * Destructor.
         */
        virtual ~Scene();

        /**
         * Accessor for the scene's entity manager.
         *
         * @return Entity manager for the scene.
         */
        EntityManager& entities();

        /**
         * Checks whether the scene has a camera entity.
         *
         * @return True if the scene has a camera entity, false otherwise.
         */
        bool has_camera() const;

        /**
         * Accessor for the entity currently serving as the camera for the scene.
         *
         * @return Pointer to the camera entity.
         */
        WatchPtr<Entity> camera() const;

        /**
         * Sets the entity to serve as the scene's camera.
         *
         * @param camera_entity Pointer to the entity that should serve as the scene's camera.
         */
        void camera(WatchPtr<Entity> camera_entity);

        /**
         * Creates a new entity in the scene.
         *
         * Sets the child entity's name to the empty string.
         *
         * @return Pointer to the created entity.
         */
        WatchPtr<Entity> create_entity();

        /**
         * Creates a new entity in the scene.
         *
         * @param entity_name Unique name for the entity.
         * @return Pointer to the created entity.
         */
        WatchPtr<Entity> create_entity(const std::string& entity_name);

        /**
         * Publishes an event to be dispatched to all subscribers of the specified `event_name` on this scene.
         *
         * The event must be passed as a shared pointer to the event. This is because we make no assumption about how
         * subscribers may choose to use the event. For instance, we cannot guarantee that subscribers will not make
         * use of the event beyond the lifetime of their callback function.
         *
         * @param event_name Name of the event to publish.
         * @param Shared pointer to the event to be published.
         */
        void publish(const std::string& event_name, std::shared_ptr<suborbital::Event> event);

        /**
         * Broadcasts an event to the scene and every entity in the scene.
         *
         * The event must be passed as a shared pointer to the event. This is because we make no assumption about how
         * subscribers may choose to use the event. For instance, we cannot guarantee that subscribers will not make
         * use of the event beyond the lifetime of their callback function.
         *
         * @param event_name Name of the event to broadcast.
         * @param Shared pointer to the event to be broadcast.
         */
        void broadcast(const std::string& event_name, std::shared_ptr<suborbital::Event> event);

        /**
         * Subscribes to receive events of the specified `event_name`.
         *
         * The `EventSubscription` object returned manages the lifetime of the subscription. The subscription is
         * cancelled automatically once the object goes out of scope. Alternatively, it is possible to manually cancel
         * the subscription using the function provided by the `EventSubscription` class.
         *
         * @param event_name Name of the event to subscribe for.
         * @param callback Callback function that should receive the events.
         * @return Subscription object that controls the lifetime of the subscription.
         */
        std::unique_ptr<suborbital::EventSubscription> subscribe(const std::string& event_name,
                std::unique_ptr<suborbital::EventCallbackBase> callback);

        /**
         * Creates a new system to process entities in the scene.
         *
         * @return Pointer to the created system.
         */
        template<typename SystemType>
        WatchPtr<SystemType> create_system()
        {
            SystemType* system_ptr = new SystemType();
            const std::string system_name = system_registry().system_name<SystemType>();

            assert(m_systems.find(system_name) == m_systems.end());
            m_systems[system_name] = std::unique_ptr<SystemType>(system_ptr);

            system_ptr->m_scene = this;
            system_ptr->create();
            return WatchPtr<SystemType>(system_ptr);
        }

        /**
         * Creates and attaches a system of the type specified by `class_name` to the scene and returns a pointer
         * to the created system.
         *
         * @param class_name Class name for the attribute to be created and attached.
         * @return Pointer to the attribute that was created and attached.
         */
        WatchPtr<System> create_system(const std::string& class_name);

        /**
         * Accessor for the system with the specified name.
         *
         * @param name Name of the system to return.
         * @return Pointer to the system with the specified name.
         */
        template<typename SystemType>
        WatchPtr<SystemType> system(const std::string& name)
        {
            auto iter = m_systems.find(name);
            if (iter != m_systems.end())
            {
                std::unique_ptr<System>& system = iter->second;
                SystemType* specific_system = dynamic_cast<SystemType*>(system.get());

                if (specific_system)
                {
                    return WatchPtr<SystemType>(specific_system);
                }
            }

            return nullptr;
        }

        /**
         * Accessor for the system with the specified name.
         *
         * @param name Name of the system to return.
         * @return Pointer to the system with the specified name.
         */
        WatchPtr<System> system(const std::string& name);

    protected:
        /**
         * Constructor.
         */
        Scene();

        /**
         * Called after the scene has been created and pushed onto the scene stack.
         */
        virtual void create() = 0;

        /**
         * Called each frame before the entities in the scene are updated.
         *
         * @param dt Time elapsed (in seconds) since the previous call to update.
         */
        virtual void update(double dt) = 0;

        /**
         * Called immediately before another scene is made current.
         */
        virtual void suspend() = 0;

        /**
         * Called immediately after the scene is made current again.
         */
        virtual void resume() = 0;

    private:
        /**
         * Called each frame.
         *
         * The scene is processed in the following order:
         *
         * 1. The scene's `update` function is called.
         * 2. The scene's systems are processed.
         * 3. All the entities in the scene are recursively updated.
         * 4. Entities marked for destruction are deleted.
         *
         * @param dt Time elapsed (in seconds) since the previous call to process.
         */
        void process(double dt);

    private:
        /**
         * Entities that form the contents of the scene.
         */
        EntityManager m_entities;

        /**
         * The entity serving as the scene's camera.
         */
        WatchPtr<Entity> m_camera;

        /**
         * Event dispatcher for the scene.
         */
        std::unique_ptr<EventDispatcher> m_event_dispatcher;

        /**
         * The systems that process the entities in the scene.
         *
         * Map from system names to systems.
         */
        std::map<std::string, std::unique_ptr<System>> m_systems;
    };
}

#endif