#ifndef SUBORBITAL_SPECIFIC_SCENE_FACTORY_HPP
#define SUBORBITAL_SPECIFIC_SCENE_FACTORY_HPP

namespace suborbital
{
    template<typename SceneType>
    class SpecificSceneFactory : public SceneFactory
    {
    public:
        /**
         * Constructor.
         */
        SpecificSceneFactory() = default;

        /**
         * Destructor.
         */
        ~SpecificSceneFactory() = default;

        /**
         * Instantiates a scene of the templated type and returns a unique_ptr to the created scene.
         *
         * @return Unique pointer to the created component.
         */
        std::unique_ptr<Scene> create() const
        {
            return std::unique_ptr<SceneType>(new SceneType());
        }
    };
}

#endif