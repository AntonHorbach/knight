#include "Systems.hpp"

CollisionSystem::CollisionSystem(Manager* manager): System(manager)
{}

void CollisionSystem::update() {
    std::vector<shEntity> colliderEntities;

    for(auto& entity : manager->getEntities()) {
        if(entity->hasComponent<ColliderComponent>())
        {
            colliderEntities.push_back(entity);
        }
    }

    for(size_t i = 0; i < colliderEntities.size(); ++i) {
        TransformComponent& tcI = colliderEntities[i]->getComponent<TransformComponent>();
        SpriteComponent& scI = colliderEntities[i]->getComponent<SpriteComponent>();

        for(size_t j = i + 1; j < colliderEntities.size(); ++j) {
            TransformComponent& tcJ = colliderEntities[j]->getComponent<TransformComponent>();
            SpriteComponent& scJ = colliderEntities[j]->getComponent<SpriteComponent>();

            if(tcI.position.x + scI.dst.w >= tcJ.position.x
                && tcJ.position.x + scJ.dst.w >= tcI.position.x
                && tcI.position.y + scI.dst.h >= tcJ.position.y
                && tcJ.position.y + scJ.dst.h >= tcI.position.y)
            {
                tcI.position.x = scI.dst.x;
                tcI.position.y = scI.dst.y;

                if(colliderEntities[i]->hasComponent<JumperComponent>()) {
                    JumperComponent& jc = colliderEntities[i]->getComponent<JumperComponent>();

                    jc.jumping = false;
                    jc.comingDown ^= true;
                }
            }
        }
    }
}