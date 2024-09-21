#include <cmath>

#include "vec3.h"

vec3 operator+(const vec3 &l, const vec3 &r)
{
    return vec3(l.x + r.x, l.y + r.y, l.z + r.z);
}

vec3 operator-(const vec3 &l, const vec3 &r)
{
    return vec3(l.x - r.x, l.y - r.y, l.z - r.z);
}

vec3 operator*(const vec3 &v, float f)
{
    return vec3(v.x * f, v.y * f, v.z * f);
}

vec3 operator*(const vec3 &l, const vec3 &r)
{
    return vec3(l.x * r.x, l.y * r.y, l.z * r.z);
}

float dot(const vec3 &l, const vec3 &r)
{
    return l.x * r.x + l.y * r.y + l.z * r.z;
}

float lenSq(const vec3& v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

float len(const vec3& v)
{
    float lsq = lenSq(v);
    if (lsq < VEC3_EPSILON)
    {
        return 0.0f;
    }
    return sqrtf(lsq);
}