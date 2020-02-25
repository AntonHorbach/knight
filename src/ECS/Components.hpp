#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "ECS.hpp"
#include "../math/vec2.hpp"

struct TransformComponent: public Component {
    vec2f position;
    vec2f velocity;

    TransformComponent(vec2f pos, vec2f v)
            : position(pos), velocity(v)
    {}
};

#endif