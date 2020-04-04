#include "Systems.hpp"

MovementSystem::MovementSystem(Manager* manager)
    :System(manager)
{
}

void MovementSystem::update() {
    for(const shEntity& entity : manager->getEntities()) {
        if(entity->hasComponent<TransformComponent>())
        {
            auto& tc = entity->getComponent<TransformComponent>();
            auto& sc = entity->getComponent<SpriteComponent>();

            tc.position.x += tc.velocity.x;
        }
    }
}