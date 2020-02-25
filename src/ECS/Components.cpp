#include "Components.hpp"

#include "../game.hpp"

TransformComponent::TransformComponent(vec2f pos, vec2f v)
    : position(pos), velocity(v)
{}

SpriteComponent::SpriteComponent(SDL_Rect _src, SDL_Rect _dst, const std::string& text_id)
    : src(_src), dst(_dst), texture_id(text_id)
{}