// Copyright Bruce Wade, 2024

#include <cmath>

#include "vec3.h"

vec3 operator+(const vec3& l, const vec3& r)
{
    return vec3{l.x + r.x, l.y + r.y, l.z + r.z};
}

vec3 operator-(const vec3& l, const vec3& r)
{
    return vec3{l.x - r.x, l.y - r.y, l.z - r.z};
}

vec3 operator*(const vec3& v, const float f)
{
    return vec3{v.x * f, v.y * f, v.z * f};
}

vec3 operator*(const vec3& l, const vec3& r)
{
    return vec3{l.x * r.x, l.y * r.y, l.z * r.z};
}

bool operator==(const vec3& l, const vec3& r)
{
    const vec3 diff(l - r);
    return lenSq(diff) < VEC3_EPSILON;
}

bool operator!=(const vec3& l, const vec3& r)
{
    return !(l == r);
}

/**
 * Dot Product
 * - If positive the vectors point in the same direction
 * - If negative the vectors point in the opposite directions
 * - If zero the vectors are perpendicular
 * @param l first vector
 * @param r second vector
 * @return 
 */
float dot(const vec3& l, const vec3& r)
{
    return l.x * r.x + l.y * r.y + l.z * r.z;
}

/**
 * Length Squared
 * - Use Pythagorean theorem x^2 + y^2 + z^2
 * @param v vector for calculation
 * @return length without using sqrtf
 */
float lenSq(const vec3& v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

/**
 * Length
 * - Calculates the length using the sqrtf ensuring to handle zero.
 * E.G: Useful for finding the distance between two vectors
 * distance = len(vec1 - vec2)
 * @param v vector for calculation
 * @return length with using sqrtf
 */
float len(const vec3& v)
{
    const float lsq = lenSq(v);
    if (lsq < VEC3_EPSILON)
    {
        return 0.0f;
    }
    return sqrtf(lsq);
}

/**
 * Calculates the unit vector using sqrtf normalizes inplace
 * @param v 
 */
void normalize(vec3& v)
{
    const float lsq = lenSq(v);
    if (lsq < VEC3_EPSILON)
    {
        return;
    }

    const float invLen = 1.0f / sqrtf(lsq);
    v.x *= invLen;
    v.y *= invLen;
    v.z *= invLen;
}

/**
 * Calculates the unit vector without using sqrtf does not modify the input vector
 * @param v 
 * @return new normalized vector
 */
vec3 normalized(const vec3& v)
{
    const float lsq = lenSq(v);
    if (lsq < VEC3_EPSILON)
    {
        return v;
    }

    const float invLen = 1.0f / sqrtf(lsq);
    return vec3{
        v.x * invLen,
        v.y * invLen,
        v.z * invLen
    };
}

/**
 * Calculate the angle between two vectors
 * @param l 
 * @param r 
 * @return angle in radians, to get degrees multipy by 57.2958f
 */
float angle(const vec3& l, const vec3& r)
{
    const float sqMagL = lenSq(l);
    const float sqMagR = lenSq(r);

    if (sqMagL < VEC3_EPSILON || sqMagR < VEC3_EPSILON)
    {
        return 0.0f;
    }

    const float dotP = dot(l, r);
    const float len = sqrtf(sqMagL) * sqrtf(sqMagR);
    return acosf(dotP / len);
}

/**
 * Calculates a new vector with the length of A in the direction of B
 * @param a 
 * @param b 
 * @return 
 */
vec3 project(const vec3& a, const vec3& b)
{
    const float magBSq = len(b);
    if (magBSq < VEC3_EPSILON)
    {
        return vec3{};
    }

    const float scale = dot(a, b) / magBSq;
    return b * scale;
}

vec3 reject(const vec3& a, const vec3& b)
{
    const vec3 projection = project(a, b);
    return a - projection;
}

vec3 reflect(const vec3& a, const vec3& b)
{
    const float magBSq = len(b);
    if (magBSq < VEC3_EPSILON)
    {
        return vec3{};
    }
    const float scale = dot(a, b) / magBSq;
    const vec3 proj2 = b * (scale * 2);
    return a - proj2;
}

/**
 * Calculates a vector that is perpendicular to l and r vectors
 * @param l 
 * @param r 
 * @return 
 */
vec3 cross(const vec3& l, const vec3& r)
{
    return vec3{
        l.y * r.z - l.z * r.y,
        l.z * r.x - l.x * r.z,
        l.x * r.y - l.y * r.x
    };
}

vec3 lerp(const vec3& s, const vec3& e, const float t)
{
    return vec3{
        s.x + (e.x - s.x) * t,
        s.y + (e.y - s.y) * t,
        s.z + (e.z - s.z) * t
    };
}

vec3 slerp(const vec3& s, const vec3& e, const float t)
{
    if (t < 0.01f)
    {
        return lerp(s, e, t);
    }

    const vec3 from = normalized(s);
    const vec3 to = normalized(e);
    const float theta = angle(from, to);
    const float sin_theta = sinf(theta);
    const float a = sinf((1.0f - t) * theta) / sin_theta;
    const float b = sinf(t * theta) / sin_theta;
    return from * a + to * b;
}

vec3 nlerp(const vec3& s, const vec3& e, const float t)
{
    const vec3 linear{
        s.x + (e.x - s.x) * t,
        s.y + (e.y - s.y) * t,
        s.z + (e.z - s.z) * t
    };
    return normalized(linear);
}