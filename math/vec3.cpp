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