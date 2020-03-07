#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <SDL2/SDL.h>

#include "ECS.hpp"
#include "../math/vec2.hpp"
#include "../AssetsManager.hpp"

struct TransformComponent: public Component {
    vec2f position;
    vec2f velocity = {0, 0};
    vec2f speed;

    TransformComponent(vec2f pos, vec2f speed);
};

enum Animations {
    NONE, WALK
};

struct SpriteComponent: public Component {
    SDL_Rect src;
    SDL_Rect dst;
    std::string texture_id;
    Animations current_animation;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    bool animation;

    SpriteComponent(SDL_Rect _src, SDL_Rect _dst,
                    const std::string& text_id, bool animation = false);
};

struct KeybordInput: public Component {};

struct JumperComponent: public Component {
    float height;
    float baseY;

    JumperComponent(float h);
};

struct ColliderComponent: public Component {
    SDL_Rect dst;

    ColliderComponent(SDL_Rect dst);
};

#endif