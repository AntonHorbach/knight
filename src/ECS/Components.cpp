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

void insert(std::map<AnimationInd, Animation>& col, Animation anim) {
    AnimationInd key = anim.animationName;

    col.insert({key, std::move(anim)});
}

std::istream& operator>>(std::istream& stream, Animation& anim) {
    auto& [name, ind, frames, offset, speed, cyclic, p, b] = anim;
    size_t intName = 0;

    stream >> intName >> ind >> frames >> offset >> speed >> cyclic;
    name = (AnimationInd)intName;

    return stream;
}

void insert(std::map<AttackType, Attack>& col, Attack attack) {
    AttackType key = attack.type;

    col.insert({key, std::move(attack)});
}

std::istream& operator>>(std::istream& stream, Attack& attack) {
    auto& [type, anim, dmg, speed, radius, times] = attack;
    size_t intType = 0, intAnim = 0;

    stream >> intType >> intAnim >> dmg >> speed >> radius >> times;
    type = (AttackType)intType;
    anim = (AnimationInd)intAnim;

    return stream;
}