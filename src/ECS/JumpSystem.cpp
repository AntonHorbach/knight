#include "Systems.hpp"


JumpSystem::JumpSystem(Manager* manager): System(manager)
{}

void JumpSystem::update() {
    for(const shEntity& entity : manager->getEntities()) {
        if(entity->hasComponent<TransformComponent>()
            && entity->hasComponent<JumperComponent>())
        {
            TransformComponent& tc = entity->getComponent<TransformComponent>();
            JumperComponent& jc = entity->getComponent<JumperComponent>();
            
            if((tc.velocity.y < 0.f) && (jc.baseY - jc.height == tc.position.y)) {
                tc.velocity.y = tc.speed.y;
            }

            tc.position.y += tc.velocity.y;
        }
    }
}