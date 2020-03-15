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
                    sc.flip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_d:
                    tc.velocity.x = tc.speed.x;
                    sc.flip = SDL_FLIP_NONE;
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
                default:
                    break;
                }
            }

            tc.position.x += tc.velocity.x;

            if(tc.velocity.x != 0.f && sc.current_animation == "idle") {
                sc.current_animation = "walk";
            }
            else if(tc.velocity.x == 0.f && sc.current_animation == "walk") {
                sc.current_animation = "idle";
            }
        }
    }
}