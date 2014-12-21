#include <iostream>
#include <memory>

#include <suborbital/Suborbital.hpp>
#include <suborbital/PythonInterpreter.hpp>

using namespace suborbital;

int main(int argc, char* argv[])
{
    PythonInterpreter script_interpreter;
    script_interpreter.add_path("/Users/Omar/Documents/Suborbital/build/lib");
    script_interpreter.add_path("/Users/Omar/Documents/Suborbital/examples/scripting/resources/scripts");

    {
        Entity entity("Player");
        Behaviour* timer_behaviour = entity.create_behaviour("TimerBehaviour");
        for (int i = 0; i < 10; ++i)
        {
            timer_behaviour->update(0.1);
        }
    }

    std::cout << "End of program." << std::endl;
}