#ifndef VEC2_HPP
#define VEC2_HPP

struct vec2f {
    float x;
    float y;

    vec2f& add(const vec2f& oth);
    vec2f& sub(const vec2f& oth);

    friend vec2f operator+(vec2f left, const vec2f& right);
    friend vec2f operator-(vec2f left, const vec2f& right);
};

#endif