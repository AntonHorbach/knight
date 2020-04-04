#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <SDL2/SDL.h>

#include <map>

#include "ECS.hpp"
#include "../math/vec2.hpp"

struct TransformComponent: public Component {
    vec2f position;
    vec2f velocity = {0, 0};
    vec2f speed;

    TransformComponent(vec2f pos, vec2f speed);
};

enum class AnimationInd: size_t {
    IDLE = 0, WALK, JUMP, DOUBLE_ATTACK
};

struct Animation {
    AnimationInd animationName;
    size_t ind;
    size_t frames;
    size_t speed;
    bool cyclic = true;
    bool played = false;
    size_t beginTime = 0;
};

struct SpriteComponent: public Component {
    SDL_Rect src;
    SDL_Rect dst;
    std::string texture_id;
    Animation* current_animation = nullptr;
    std::map<AnimationInd, Animation> animations;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    bool animation;

    SpriteComponent(SDL_Rect src, SDL_Rect dst, std::string text_id,
                    bool animation = false);
};

struct KeyboardInput: public Component {};

struct JumperComponent: public Component {
    float height;
    float baseY;

    explicit JumperComponent(float h);
};

struct ColliderComponent: public Component {
    SDL_Rect dst;

    explicit ColliderComponent(SDL_Rect dst);
};

struct HealthComponent: public Component {
    float max_health = 100.f;
    float regen = 0.1f;
    float health = max_health;

    HealthComponent() = default;
    HealthComponent(float health, float regen);
};

enum class AttackType {
    DOUBLE_ATTACK
};

struct Attack {
    AttackType type;
    AnimationInd animation;
    float dmg;
    float speed;
    float radius;
    size_t times;
};

struct AttackComponent: public Component {
    std::map<AttackType, Attack> attacks;
    Attack* current_attack = nullptr;
    bool attacking = false;
};

#endif