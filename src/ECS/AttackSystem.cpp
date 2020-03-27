#include "Systems.hpp"

AttackSystem::AttackSystem(Manager* m): System(m)
{}

void AttackSystem::update() {
    std::vector<shEntity> attackers;
    std::vector<shEntity> victims;
    
    for(auto& entity : manager->getEntities()) {
        if(entity->hasComponent<AttackComponent>()
            && entity->getComponent<AttackComponent>().attacking)
        {
            attackers.push_back(entity);
        }

        if(entity->hasComponent<HealthComponent>()) {
            victims.push_back(entity);
        }
    }

    for(auto& attacker : attackers) {
        auto& ccA = attacker->getComponent<ColliderComponent>();
        auto& tcA = attacker->getComponent<TransformComponent>();
        auto& ac = attacker->getComponent<AttackComponent>();
        
        for(auto& victim : victims) {
            if(attacker != victim) {
                auto& ccV = victim->getComponent<ColliderComponent>();
                auto& tcV = victim->getComponent<TransformComponent>();

                if((tcA.position.x + ccA.dst.x + ccA.dst.w + 15 >= tcV.position.x + ccV.dst.x)
                    &&
                    (tcA.position.x + ccA.dst.x + ccA.dst.w + 15 <= tcV.position.x + ccV.dst.x + ccV.dst.w)
                    &&
                    (tcA.position.y + ccA.dst.y + (ccA.dst.w / 2)) >= (tcV.position.y + ccV.dst.y)
                    &&
                    (tcA.position.y + ccA.dst.y + (ccA.dst.w / 2)) <= (tcV.position.y + ccV.dst.y + ccV.dst.h))
                {
                    auto& hc = victim->getComponent<HealthComponent>();
                    auto& sc = attacker->getComponent<SpriteComponent>();

                    hc.health -= ac.current_attack->dmg;
                }
            }
        }
    }
}