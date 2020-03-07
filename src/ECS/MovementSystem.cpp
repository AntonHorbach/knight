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
            SpriteComponent& sc = entity->getComponent<SpriteComponent>();
            
            if(Game::event.type == SDL_KEYDOWN) {
                switch(Game::event.key.keysym.sym) {
                case SDLK_a:
                    tc.velocity.x = -tc.speed.x;
                    sc.current_animation = Animations::WALK;
                    sc.flip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_d:
                    tc.velocity.x = tc.speed.x;
                    sc.current_animation = Animations::WALK;
                    break;
                default:
                    break;
                }
            }
            else if(Game::event.type == SDL_KEYUP) {
                switch(Game::event.key.keysym.sym) {
                case SDLK_a:
                case SDLK_d:
                    sc.src.x = 0;
                    tc.velocity.x = 0;
                    sc.current_animation = Animations::NONE;
                    sc.flip = SDL_FLIP_NONE;
                default:
                    break;
                }
            }

            tc.position.x += tc.velocity.x;
        }
    }
}