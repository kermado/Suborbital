#include <iostream>

#include <suborbital/Suborbital.hpp>
#include <suborbital/PythonInterpreter.hpp>
#include <suborbital/component/ExampleAttribute.hpp>

#include "ExampleScene.hpp"

using namespace suborbital;

int main(int argc, char* argv[])
{
    PythonInterpreter script_interpreter;
    script_interpreter.add_path("/Users/Omar/Documents/Suborbital/build/lib");
    script_interpreter.add_path("/Users/Omar/Documents/Suborbital/examples/scripting/resources/scripts");

    REGISTER_ATTRIBUTE(ExampleAttribute);

    {
        ExampleScene scene;
        WatchPtr<Entity> entity = scene.create_entity("Player");
        entity->create_attribute<ExampleAttribute>();
        entity->create_attribute("HealthAttribute");
        entity->create_behaviour("ExampleBehaviour");

        for (int i = 0; i < 10; ++i)
        {
            scene.process(0.1);
        }

        std::cout << "End of scope." << std::endl;
    }

    std::cout << "End of program." << std::endl;

    return 0;
}