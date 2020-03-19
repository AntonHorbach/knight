#include "Components.hpp"

#include "../game.hpp"

TransformComponent::TransformComponent(vec2f pos, vec2f s)
    : position(pos), speed(s)
{}

SpriteComponent::SpriteComponent(SDL_Rect _src, SDL_Rect _dst,
                    const std::string& text_id, bool anim)
    : src(_src), dst(_dst), texture_id(text_id), animation(anim)
{}

JumperComponent::JumperComponent(float h): height(h)
{}

ColliderComponent::ColliderComponent(SDL_Rect d): dst(d)
{}