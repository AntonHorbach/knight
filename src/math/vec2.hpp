#ifndef VEC2_HPP
#define VEC2_HPP

template <typename T>
struct vec2;

using vec2f = vec2<float>;

template <typename T>
struct vec2 {
    T x;
    T y;

    vec2& operator+=(const vec2& oth) {
        x += oth.x;
        y += oth.y;

        return *this;
    }

    vec2& operator-=(const vec2& oth) {
        x -= oth.x;
        y -= oth.y;

        return *this;
    }

    friend vec2 operator+(const vec2& left, const vec2& right) {
        vec2 res = left;
        res += right;
        return res;
    }

    friend vec2 operator-(const vec2& left, const vec2& right) {
        vec2 res = left;
        res -= right;
        return res;
    }
};

#endif