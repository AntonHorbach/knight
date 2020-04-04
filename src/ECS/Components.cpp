#include "Components.hpp"

TransformComponent::TransformComponent(vec2f pos, vec2f s)
    : position(pos), speed(s)
{}

SpriteComponent::SpriteComponent(SDL_Rect _src, SDL_Rect _dst,
                    std::string text_id, bool anim)
    : src(_src), dst(_dst), texture_id(std::move(text_id)), animation(anim)
{}

JumperComponent::JumperComponent(float h): height(h), baseY(0.f)
{}

ColliderComponent::ColliderComponent(SDL_Rect d): dst(d)
{}

HealthComponent::HealthComponent(float h, float r)
    : max_health(h), regen(r)
{}