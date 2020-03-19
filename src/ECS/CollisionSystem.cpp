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
        ColliderComponent& ccI = colliderEntities[i]->getComponent<ColliderComponent>();

        for(size_t j = i + 1; j < colliderEntities.size(); ++j) {
            TransformComponent& tcJ = colliderEntities[j]->getComponent<TransformComponent>();
            SpriteComponent& scJ = colliderEntities[j]->getComponent<SpriteComponent>();
            ColliderComponent& ccJ = colliderEntities[j]->getComponent<ColliderComponent>();

            if(tcI.position.x + ccI.dst.x + ccI.dst.w >= tcJ.position.x + ccJ.dst.x
                && tcJ.position.x + ccJ.dst.x + ccJ.dst.w >= tcI.position.x + ccI.dst.x
                && tcI.position.y + ccI.dst.y + ccI.dst.h >= tcJ.position.y + ccJ.dst.y
                && tcJ.position.y + ccJ.dst.y + ccJ.dst.h >= tcI.position.y + ccI.dst.y)
            {
                tcI.position.x = scI.dst.x;
                tcI.position.y = scI.dst.y;

                if(colliderEntities[i]->hasComponent<JumperComponent>() && tcI.position.y > tcJ.position.y) {
                    tcI.velocity.y = tcI.speed.y;
                }
                else {
                    tcI.velocity.y = 0.f;
                    scI.src.x = 0;
                    scI.current_animation = &scI.animations["idle"];
                }
            }
        }
    }
}