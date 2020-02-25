#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <SDL2/SDL.h>

#include "ECS.hpp"
#include "../math/vec2.hpp"
#include "../AssetsManager.hpp"

struct TransformComponent: public Component {
    vec2f position;
    vec2f velocity;

    TransformComponent(vec2f pos, vec2f v);
};

struct SpriteComponent: public Component {
    SDL_Rect src;
    SDL_Rect dst;
    std::string texture_id;

    SpriteComponent(SDL_Rect _src, SDL_Rect _dst, const std::string& text_id);
};

struct KeybordInput: public Component {};

#endif