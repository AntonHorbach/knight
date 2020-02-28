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
            TransformComponent& tc = entity->getComponent<TransformComponent>();

            if(Game::event.type == SDL_KEYDOWN) {
                switch(Game::event.key.keysym.sym) {
                case SDLK_a:
                    tc.position.x -= tc.velocity.x;
                    break;
                case SDLK_d:
                    tc.position.x += tc.velocity.x;
                    break;
                default:
                    break;
                }
            }
        }
    }
}