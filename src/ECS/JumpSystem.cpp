#include "Systems.hpp"


JumpSystem::JumpSystem(Manager* manager): System(manager)
{}

void JumpSystem::update() {
    for(const shEntity& entity : manager->getEntities()) {
        if(entity->hasComponent<TransformComponent>()
            && entity->hasComponent<KeybordInput>()
            && entity->hasComponent<JumperComponent>())
        {
            TransformComponent& tc = entity->getComponent<TransformComponent>();
            JumperComponent& jc = entity->getComponent<JumperComponent>();
            SpriteComponent& sc = entity->getComponent<SpriteComponent>();

            if(Game::event.type == SDL_KEYDOWN) {
                switch(Game::event.key.keysym.sym) {
                case SDLK_w: {
                    if(tc.velocity.y == 0.f) {
                        tc.velocity.y = -tc.speed.y;
                        jc.baseY = tc.position.y;
                        sc.current_animation = "jump";
                    }
                    break;
                }
                case SDLK_s: {
                    if(tc.velocity.y < 0.f) {
                        tc.velocity.y = tc.speed.y;
                    }

                    break;
                }
                default:
                    break;
                }
            }
            
            if((tc.velocity.y < 0.f) && (jc.baseY - jc.height == tc.position.y)) {
                tc.velocity.y = tc.speed.y;
            }

            tc.position.y += tc.velocity.y;
        }
    }
}