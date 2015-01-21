#ifndef SUBORBITAL_SYSTEM_HPP
#define SUBORBITAL_SYSTEM_HPP

#include <string>

#include <suborbital/NonCopyable.hpp>
#include <suborbital/Watchable.hpp>

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

    protected:
        /**
         * Constructor.
         *
         * @param scene Reference to the parent scene.
         */
        System(Scene& scene);

        /**
         * Called each frame.
         *
         * @param dt Time elapsed (in seconds) since the previous call to process.
         */
        virtual void process(double dt) = 0;

    protected:
        /**
         * Scene that the system is processing.
         */
        Scene& m_scene;
    };
}

#endif