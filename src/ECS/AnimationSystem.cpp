#include "Systems.hpp"

AnimationSystem::AnimationSystem(Manager* m): System(m)
{}

void AnimationSystem::update() {
    for(auto& entity : manager->getEntities()) {
        if(entity->hasComponent<SpriteComponent>()) {
            auto& sc = entity->getComponent<SpriteComponent>();

            if(sc.animation) {
                auto& tc = entity->getComponent<TransformComponent>();
                auto& jc = entity->getComponent<JumperComponent>();
                
                if(sc.current_animation == nullptr)
                {
                    sc.current_animation = &sc.animations["idle"];
                    sc.current_animation->beginTime = SDL_GetTicks();
                    sc.src.x = 0;
                }

                if(tc.velocity.x != 0.f) {
                    if(tc.velocity.y == 0.f
                        && sc.current_animation != &sc.animations["walk"])
                    {
                        sc.current_animation = &sc.animations["walk"];
                        sc.current_animation->beginTime = SDL_GetTicks();
                    }
                }
                else if (tc.velocity.y != 0.f) {
                    if(sc.current_animation != &sc.animations["jump"]) {
                        sc.current_animation = &sc.animations["jump"];
                        sc.current_animation->beginTime = SDL_GetTicks();
                    }
                }
                else if(sc.current_animation != &sc.animations["idle"]) {
                    sc.current_animation = &sc.animations["idle"];
                    sc.current_animation->beginTime = SDL_GetTicks();
                }

                Animation* anim = sc.current_animation;

                if(anim->cyclic && anim->played) {
                    anim->played = false;
                    anim->beginTime = SDL_GetTicks();
                }
                else if(!anim->cyclic && anim->played) {
                    anim->played = false;
                    sc.current_animation = &sc.animations["idle"];
                    anim = sc.current_animation;
                    anim->beginTime = SDL_GetTicks();
                    sc.src.x = 0;
                }
                
                sc.src.y = anim->ind * sc.src.h;
                sc.src.x = sc.src.w * static_cast<int>(
                        ((SDL_GetTicks() - anim->beginTime) / anim->speed) % anim->frames
                );

                if(sc.src.x == (sc.src.w * (anim->frames - 1)))
                {
                    anim->played = true;
                }
            }
        }
    }
}