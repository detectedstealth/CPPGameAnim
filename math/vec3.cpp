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

vec3 project(const vec3& a, const vec3& b)
{
    float magBSq = len(b);
    if (magBSq < VEC3_EPSILON)
    {
        return vec3();
    }

    float scale = dot(a, b) / magBSq;
    return b * scale;
}

vec3 reject(const vec3& a, const vec3& b)
{
    vec3 projection = project(a, b);
    return a - projection;
}

vec3 reflect(const vec3& a, const vec3 &b)
{
    float magBSq = len(b);
    if (magBSq < VEC3_EPSILON)
    {
        return vec3();
    }
    float scale = dot(a, b) / magBSq;
    vec3 proj2 = b * (scale * 2);
    return a - proj2;
}

vec3 cross(const vec3& l, const vec3& r)
{
    return vec3(
        l.y * r.z - l.z * r.y,
        l.z * r.x - l.x * r.z,
        l.x * r.y - l.y * r.x
    );
}