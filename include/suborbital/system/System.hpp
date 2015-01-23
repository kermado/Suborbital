#ifndef SUBORBITAL_SYSTEM_HPP
#define SUBORBITAL_SYSTEM_HPP

#include <string>

#include <suborbital/NonCopyable.hpp>
#include <suborbital/Watchable.hpp>
#include <suborbital/WatchPtr.hpp>

namespace suborbital
{
    // Forward declarations.
    class Scene;
    class EntitySet;

    class System : public Watchable, private NonCopyable
    {
    friend Scene;
    public:
        /**
         * Destructor.
         */
        virtual ~System();

        /**
         * Accessor for the scene that owns the system.
         *
         * @return Pointer to the parent scene.
         */
        WatchPtr<Scene> scene() const;

    protected:
        /**
         * Constructor.
         */
        System();

        /**
         * Called after the system has been created and attached to the scene.
         */
        virtual void create() = 0;

        /**
         * Called each frame.
         *
         * @param dt Time elapsed (in seconds) since the previous call to process.
         */
        virtual void process(double dt) = 0;

    protected:
        /**
         * Pointer to the scene that the system is processing.
         */
        WatchPtr<Scene> m_scene;
    };
}

#endif