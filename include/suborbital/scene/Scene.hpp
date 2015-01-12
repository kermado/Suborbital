#ifndef SUBORBITAL_SCENE_HPP
#define SUBORBITAL_SCENE_HPP

#include <memory>
#include <vector>

#include <suborbital/Watchable.hpp>
#include <suborbital/WatchPtr.hpp>
#include <suborbital/NonCopyable.hpp>

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
         * Sets the child entity's name to the empty string.
         *
         * @return Pointer to the created entity.
         */
        WatchPtr<Entity> create_entity(const std::string& name);

        /**
         * Searches for an entity with the specified `name` and returns it.
         *
         * A nullptr is returned if no entity having the specified `name` was found. Note that this function has time
         * complexity O(n). Avoid calling this function every frame and cache the result where possible.
         *
         * @param name Name of the entity to search for.
         * @return Pointer to the first entity found having the specified `name`.
         */
        WatchPtr<Entity> find(const std::string& name) const;

        /**
         * Broadcasts an event to every entity in the scene.
         *
         * The event must be passed as a shared pointer to the event. This is because we make no assumption about how
         * subscribers may choose to use the event. For instance, we cannot guarantee that subscribers will not make
         * use of the event beyond the lifetime of their callback function.
         *
         * @param event_name Name of the event to broadcast.
         * @param Shared pointer to the event to be broadcast.
         */
        void broadcast(const std::string& event_name, std::shared_ptr<suborbital::Event> event);

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
         * Calls the scene's `update` function and then recursively updates all entities in the scene.
         */
        void process(double dt);

    private:
        /**
         * All the entities in the scene.
         */
        std::vector<std::unique_ptr<Entity>> m_entities;

        /**
         * The entity serving as the scene's camera.
         */
        WatchPtr<Entity> m_camera;
    };
}

#endif