#ifndef SUBORBITAL_SCENE_FACTORY_HPP
#define SUBORBITAL_SCENE_FACTORY_HPP

#include <memory>

#include <suborbital/NonCopyable.hpp>

namespace suborbital
{
    // Forward declarations.
    class Scene;

    /**
     * The base class for factories that instantiate scenes.
     */
    class SceneFactory : private NonCopyable
    {
    public:
        /**
         * Constructor.
         */
        SceneFactory() = default;

        /**
         * Destructor.
         */
        virtual ~SceneFactory() = default;

        /**
         * Instantiates a scene and returns a unique_ptr to the created scene.
         *
         * @return Unique pointer to the created component.
         */
        virtual std::unique_ptr<Scene> create() const = 0;
    };
}

#endif