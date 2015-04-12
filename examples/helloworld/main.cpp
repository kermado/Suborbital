#include <suborbital/Suborbital.hpp>
#include <suborbital/PythonInterpreter.hpp>
#include <suborbital/scene/SceneStack.hpp>

using namespace suborbital;

int main(int argc, char* argv[])
{
    PythonInterpreter interpreter;
    interpreter.add_path("/Users/Omar/Documents/Suborbital/build/lib");
    interpreter.add_path("/Users/Omar/Documents/Suborbital/examples/helloworld");

    SceneStack scenes;
    scenes.register_scene("MyScene");
    scenes.push("MyScene");

    return 0;
}