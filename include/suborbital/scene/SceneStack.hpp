#ifndef SUBORBITAL_SCENE_STACK_HPP
#define SUBORBITAL_SCENE_STACK_HPP

#include <string>
#include <memory>
#include <stack>
#include <unordered_map>

#include <suborbital/NonCopyable.hpp>
#include <suborbital/WatchPtr.hpp>
#include <suborbital/scene/Scene.hpp>
#include <suborbital/scene/PythonScene.hpp>
#include <suborbital/scene/SceneFactory.hpp>
#include <suborbital/scene/SpecificSceneFactory.hpp>
#include <suborbital/scene/PythonSceneFactory.hpp>

namespace suborbital
{
    class SceneStack : private NonCopyable
    {
    public:
        /**
         * Constructor.
         */
        SceneStack();

        /**
         * Destructor.
         */
        ~SceneStack();

        /**
         * Registers a scene under the provided `name` to be instantiated at some point in the future.
         *
         * @param name Unique name to identify the scene.
         */
        template<typename SceneType>
        void register_scene(const std::string& name)
        {
            std::unique_ptr<SceneFactory> factory(new SpecificSceneFactory<SceneType>());
            m_factories.insert(std::make_pair(name, std::move(factory)));
        }

        /**
         * Registers a Python defined scene under the provided `name` to be instantiated at some point in the future.
         *
         * @param name Class/file name for the scene.
         */
        void register_scene(const std::string& name)
        {
            std::unique_ptr<SceneFactory> factory(new SpecificSceneFactory<PythonScene>(name));
            m_factories.insert(std::make_pair(name, std::move(factory)));
        }

        /**
         * Checks whether there are any scenes on the stack.
         *
         * @return True if the stack is empty, false otherwise.
         */
        bool empty() const;

        /**
         * Instantiates the scene registered under the provided `name` and pushes it to the top of the stack, making
         * it the current scene.
         *
         * @param name Name of the registered scene to be instantiated and made current.
         */
        void push(const std::string& name);

        /**
         * Pops the current scene off the top of the stack.
         *
         * @note The scene will be deleted at this point.
         */
        void pop();

        /**
         * Clears all the scenes from the stack.
         *
         * @note All of the scenes on the stack will be deleted at this point.
         */
        void clear();

        /**
         * Called each frame.
         *
         * Processes the current scene at the top of the stack.
         */
        void process(double dt);

    private:
        /**
         * Stack of pointers to scenes.
         */
        std::stack<std::unique_ptr<Scene>> m_stack;

        /**
         * Factory functions for creating registered scenes.
         */
        std::unordered_map<std::string, std::unique_ptr<SceneFactory>> m_factories;
    };
}

#endif