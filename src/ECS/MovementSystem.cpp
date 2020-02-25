#include "Systems.hpp"

MovementSystem::MovementSystem(Manager* manager)
    :System(manager)
{
}

void MovementSystem::update() {
    for(const shEntity& entity : manager->getEntities()) {
        if(entity->hasComponent<TransformComponent>()) {
            TransformComponent& comp = entity->getComponent<TransformComponent>();

            comp.position.x += comp.velocity.x;
            comp.position.y += comp.velocity.y;
        }
    }
}