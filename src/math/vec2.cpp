#include "vec2.hpp"

vec2f& vec2f::add(const vec2f& oth) {
    x += oth.x;
    y += oth.y;

    return *this;
}

vec2f& vec2f::sub(const vec2f& oth) {
    x -= oth.x;
    y -= oth.y;

    return *this;
}

vec2f operator+(vec2f left, const vec2f& right) {
    return left.add(right);
}

vec2f operator-(vec2f left, const vec2f& right) {
    return left.sub(right);
}