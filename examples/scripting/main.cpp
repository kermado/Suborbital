#include <suborbital/Suborbital.hpp>
#include <suborbital/PythonInterpreter.hpp>
#include <suborbital/scene/SceneStack.hpp>

#include "ExampleAttribute.hpp"

using namespace suborbital;

// Register the C++ defined components that we expose to Python.
REGISTER_ATTRIBUTE(ExampleAttribute);

int main(int argc, char* argv[])
{
    PythonInterpreter script_interpreter;

    // Where our SWIG generated Python modules reside.
    script_interpreter.add_path("/Users/Omar/Documents/Suborbital/build/lib");

    // Where our Python scripts reside.
    script_interpreter.add_path("/Users/Omar/Documents/Suborbital/examples/scripting/resources/scripts");

    // Register and push a scene onto the stack.
    SceneStack scene_stack;
    scene_stack.register_scene("ExampleScene");
    scene_stack.push("ExampleScene");

    // Just process the scene a large number of times...
    for (int i = 0; i < 500; ++i)
    {
        scene_stack.process(0.1);
    }

    return 0;
}