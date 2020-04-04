#include "Systems.hpp"

#include "../AssetsManager.hpp"

DrawSystem::DrawSystem(Manager* manager): System(manager)
{}

void DrawSystem::update() {
    for(const shEntity& entity : manager->getEntities()) {
        if(entity->hasComponent<TransformComponent>()
            && entity->hasComponent<SpriteComponent>())
        {
            auto& sc = entity->getComponent<SpriteComponent>();
            auto& tc = entity->getComponent<TransformComponent>();
            
            sc.dst.x = tc.position.x;
            sc.dst.y = tc.position.y;
        }
    }
}

void DrawSystem::draw() {
    for(const shEntity& entity : manager->getEntities()) {
        if(entity->hasComponent<SpriteComponent>())
        {
            auto& sc = entity->getComponent<SpriteComponent>();

            Game::assetsManager.drawTexture(sc.texture_id, sc.src, sc.dst, sc.flip);
        }
    }
}