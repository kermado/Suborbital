#include <iostream>

#include <suborbital/Suborbital.hpp>
#include <suborbital/Entity.hpp>
#include <suborbital/behaviour/Behaviour.hpp>

using namespace suborbital;

int main(int argc, char* argv[])
{
    script_interpreter.add_path("/Users/Omar/Documents/Suborbital/build/lib");
    script_interpreter.add_path("/Users/Omar/Documents/Suborbital/examples/scripting/resources/scripts");

    {
        Entity entity("Player");
        behaviour::Behaviour* timer = entity.create_behaviour("Timer");
        for (int i = 0; i < 10; ++i)
        {
            timer->update(0.1);
        }
    }

    std::cout << "End of program." << std::endl;
}