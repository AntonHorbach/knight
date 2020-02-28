#include "Systems.hpp"

MovementSystem::MovementSystem(Manager* manager)
    :System(manager)
{
}

void MovementSystem::update() {
    for(const shEntity& entity : manager->getEntities()) {
        if(entity->hasComponent<TransformComponent>()
            && entity->hasComponent<KeybordInput>())
        {
            TransformComponent& comp = entity->getComponent<TransformComponent>();

            if(Game::event.type == SDL_KEYDOWN) {
                switch(Game::event.key.keysym.sym) {
                case SDLK_a:
                    comp.position.x -= comp.velocity.x;
                    break;
                case SDLK_d:
                    comp.position.x += comp.velocity.x;
                    break;
                default:
                    break;
                }
            }
        }
    }
}