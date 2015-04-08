#include <suborbital/Entity.hpp>

#include "ExampleScene.hpp"
#include "ExampleAttribute.hpp"

ExampleScene::ExampleScene()
: Scene()
{
    // Nothing to do.
}

ExampleScene::~ExampleScene()
{
    // Nothing to do.
}

void ExampleScene::create()
{
    suborbital::WatchPtr<suborbital::Entity> entity = create_entity("Player");
    entity->create_attribute<ExampleAttribute>();
    entity->create_attribute("HealthAttribute");
    entity->create_behaviour("ExampleBehaviour");
}

void ExampleScene::update(double dt)
{
    // Nothing to do.
}

void ExampleScene::suspend()
{
    // Nothing to do.
}

void ExampleScene::resume()
{
    // Nothing to do.
}