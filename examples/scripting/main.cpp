#include <iostream>
#include <memory>

#include <suborbital/Suborbital.hpp>
#include <suborbital/PythonInterpreter.hpp>
#include <suborbital/component/ExampleAttribute.hpp>

using namespace suborbital;

int main(int argc, char* argv[])
{
    PythonInterpreter script_interpreter;
    script_interpreter.add_path("/Users/Omar/Documents/Suborbital/build/lib");
    script_interpreter.add_path("/Users/Omar/Documents/Suborbital/examples/scripting/resources/scripts");

    REGISTER_ATTRIBUTE(ExampleAttribute);

    {
        Entity entity("Player");
        entity.create_attribute<ExampleAttribute>();
        entity.create_attribute("HealthAttribute");
        entity.create_behaviour("ExampleBehaviour");

        for (int i = 0; i < 10; ++i)
        {
            entity.update(0.1);
        }

        std::cout << "End of scope." << std::endl;
    }

    std::cout << "End of program." << std::endl;

    return 0;
}