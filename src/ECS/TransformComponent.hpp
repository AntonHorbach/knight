#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

#include "ECS.hpp"
#include "../math/vec2.hpp"

struct TransformComponent: public Component {
    vec2f position;
    vec2f velocity;
};

#endif