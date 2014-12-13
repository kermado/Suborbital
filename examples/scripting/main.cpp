#include <iostream>

#include <suborbital/Suborbital.hpp>
#include <suborbital/Entity.hpp>
#include <suborbital/component/Component.hpp>

using namespace suborbital;

int main(int argc, char* argv[])
{
    script_interpreter.add_path("/Users/Omar/Documents/Suborbital/build/lib");
    script_interpreter.add_path("/Users/Omar/Documents/Suborbital/examples/scripting/resources/scripts");

    {
        std::shared_ptr<Entity> entity = Entity::create("Player");
        component::Component* timer = entity->create_component("Timer");
        for (int i = 0; i < 10; ++i)
        {
            timer->update(0.1);
        }
    }

    std::cout << "End of program." << std::endl;
}