#ifndef EXAMPLES_SCRIPTING_EXAMPLE_SCENE_HPP
#define EXAMPLES_SCRIPTING_EXAMPLE_SCENE_HPP

#include <suborbital/Scene.hpp>

class ExampleScene : public suborbital::Scene
{
public:
    /**
     * Constructor.
     */
    ExampleScene();

    /**
     * Destructor.
     */
    ~ExampleScene();

    /**
     * Called each frame before the entities in the scene are updated.
     *
     * @param dt Time elapsed (in seconds) since the previous call to update.
     */
    void update(double dt);

    /**
     * Called immediately before another scene is made current.
     */
    void suspend();

    /**
     * Called immediately after the scene is made current again.
     */
    void resume();
};

#endif
