#include "Systems.hpp"

MovementSystem::MovementSystem(Manager* manager)
    :System(manager)
{
}

void MovementSystem::update() {
    for(const shEntity& entity : manager->getEntities()) {
        if(entity->hasComponent<TransformComponent>())
        {
            TransformComponent& tc = entity->getComponent<TransformComponent>();
            SpriteComponent& sc = entity->getComponent<SpriteComponent>();

            tc.position.x += tc.velocity.x;
        }
    }
}