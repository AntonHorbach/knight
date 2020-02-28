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

            if(Game::event.type == SDL_KEYDOWN) {
                switch(Game::event.key.keysym.sym) {
                case SDLK_w: {
                    if(!jc.jumping && !jc.comingDown) {
                        jc.jumping = true;
                        jc.baseY = tc.position.y;
                    }
                    break;
                }
                case SDLK_s: {
                    if(jc.jumping) {
                        jc.jumping = false;
                        jc.comingDown = true;
                    }

                    break;
                }
                default:
                    break;
                }
            }

            if(jc.jumping && (jc.baseY - jc.height < tc.position.y)) {
                tc.position.y -= tc.velocity.y;
            }
            else if(jc.comingDown && tc.position.y < jc.baseY) {
                tc.position.y += tc.velocity.y;
            }
            else if(jc.jumping && (jc.baseY - jc.height == tc.position.y)) {
                jc.jumping = false;
                jc.comingDown = true;
            }
            else if(jc.comingDown && (jc.baseY == tc.position.y)) {
                jc.comingDown = false;
            }
        }
    }
}