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

void normalize(vec3& v)
{
    float lsq = lenSq(v);
    if (lsq < VEC3_EPSILON)
    {
        return;
    }

    float invLen = 1.0f / sqrtf(lsq);
    v.x *= invLen;
    v.y *= invLen;
    v.z *= invLen;
}

vec3 normalized(const vec3& v)
{
    float lsq = lenSq(v);

    if (lsq < VEC3_EPSILON)
    {
        return v;
    }

    float invLen = 1.0f / sqrtf(lsq);

    return vec3(
        v.x * invLen,
        v.y * invLen,
        v.z * invLen
    );
}

float angle(const vec3 &l, const vec3 &r)
{
    float sqMagL = lenSq(l);
    float sqMagR = lenSq(r);

    if (sqMagL < VEC3_EPSILON || sqMagR < VEC3_EPSILON)
    {
        return 0.0f;
    }

    float dotP = dot(l, r);
    float len = sqrtf(sqMagL) * sqrtf(sqMagR);
    return acosf(dotP / len);
}