#include "Systems.hpp"

KeybordSystem::KeybordSystem(Manager* m): System(m)
{}

void KeybordSystem::update() {
    for(auto& entity : manager->getEntities()) {
        if(entity->hasComponent<KeybordInput>()) {
            auto& tc = entity->getComponent<TransformComponent>();
            auto& jc = entity->getComponent<JumperComponent>();
            auto& sc = entity->getComponent<SpriteComponent>();

            if(Game::event.type == SDL_KEYDOWN) {
                switch(Game::event.key.keysym.sym) {
                case SDLK_a: {
                    tc.velocity.x = -tc.speed.x;
                    sc.flip = SDL_FLIP_HORIZONTAL;
                } break;
                case SDLK_d: {
                    tc.velocity.x = tc.speed.x;
                    sc.flip = SDL_FLIP_NONE;
                } break;


                case SDLK_w: {
                    if(tc.velocity.y == 0.f) {
                        tc.velocity.y = -tc.speed.y;
                        jc.baseY = tc.position.y;
                    }
                } break;
                case SDLK_s: {
                    if(tc.velocity.y < 0.f) {
                        tc.velocity.y = tc.speed.y;
                    }
                } break;

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
        }
    }
}