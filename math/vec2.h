// Copyright Bruce Wade, 2024

#pragma once

template<typename T>
struct TVec2
{
    union
    {
        struct
        {
            T x;
            T y;
        };
        T v[2];
    };

    TVec2() : x{T{0}}, y{T{0}} {}
    TVec2(T x, T y) : x{x}, y{y} {}
    explicit TVec2(T* fv) : x{fv[0]}, y{fv[1]} {}
};

typedef TVec2<float> vec2;
typedef TVec2<int> ivec2;