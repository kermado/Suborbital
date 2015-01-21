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

#include <suborbital/system/System.hpp>

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

        /**
         * Creates a new system to process entities in the scene.
         *
         * @param name Name to be used for accessing the system.
         * @return Pointer to the created system.
         */
        template<typename SystemType>
        WatchPtr<SystemType> create_system(const std::string& name)
        {
            assert(m_systems.find(name) == m_systems.end());

            SystemType* system = new SystemType();
            m_systems.insert(std::make_pair(name, std::unique_ptr<SystemType>(system)));
            return WatchPtr<SystemType>(system);
        }

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
         * The systems that process the entities in the scene.
         *
         * Map from system names to systems.
         */
        std::map<std::string, std::unique_ptr<System>> m_systems;
    };
}

#endif