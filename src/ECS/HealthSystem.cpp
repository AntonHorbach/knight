#include "Systems.hpp"

HealthSystem::HealthSystem(Manager* m): System(m)
{}

void HealthSystem::update() {
    auto& entities = manager->getEntities();

    for(size_t i = 0; i < entities.size(); ++i) {
        if(entities[i]->hasComponent<HealthComponent>()) {
            auto& hc = entities[i]->getComponent<HealthComponent>();

            if(hc.health <= 0.f) {
                entities.erase(entities.begin() + i);
                --i;
            }
            else {
                hc.health += hc.regen;

                if(hc.health > hc.max_health) {
                    hc.health = hc.max_health;
                }
            }
        }
    }
}

void HealthSystem::draw() {
    for(auto& entity : manager->getEntities()) {
        if(entity->hasComponent<HealthComponent>()) {
            auto& sc = entity->getComponent<SpriteComponent>();
            auto& hc = entity->getComponent<HealthComponent>();

            SDL_Rect r1 = {sc.dst.x, sc.dst.y + 4, sc.dst.w, 5};
            SDL_Rect r2 = {
                sc.dst.x + 2, sc.dst.y + 6,
                (int)(((sc.dst.w - 4) * hc.health) / hc.max_health),
                3
            };

            Uint8 r = 0, g = 0, b = 0, a = 0;
            SDL_GetRenderDrawColor(Game::renderer, &r, &g, &b, &a);

            SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 0);
            SDL_RenderFillRect(Game::renderer, &r1);

            SDL_SetRenderDrawColor(Game::renderer, 0, 200, 0, 0);
            SDL_RenderFillRect(Game::renderer, &r2);

            SDL_SetRenderDrawColor(Game::renderer, r, g, b, a);
        }
    }
}