// Copywrite Bruce Wade, 2024

#include <cmath>

#include "mat4.h"

#include <iostream>

#include "vec3.h"

#define M4D(aRow, bCol) \
    a.v[0 * 4 + aRow] * b.v[bCol * 4 + 0] + \
    a.v[1 * 4 + aRow] * b.v[bCol * 4 + 1] + \
    a.v[2 * 4 + aRow] * b.v[bCol * 4 + 2] + \
    a.v[3 * 4 + aRow] * b.v[bCol * 4 + 3]

#define M4V4D(mRow, x, y, z, w) \
    x * m.v[0 * 4 + mRow] + \
    y * m.v[1 * 4 + mRow] + \
    z * m.v[2 * 4 + mRow] + \
    w * m.v[3 * 4 + mRow]

#define M4SWAP(x, y) \
    {float t = x; x = y; y = t;}

#define M4_3X3MINOR(x, c0, c1, c2, r0, r1, r2) \
    (x[c0 * 4 + r0] * (x[c1 * 4 + r2] - x[c1 * 4 + r2] * \
    x[c2 * 4 + r1]) - x[c1 * 4 + r0] * (x[c0 * 4 + r1] * x[c2 * 4 + r2] - \
    x[c0 * 4 + r2] * x[c2 * 4 + r1]) + x[c2 * 4 + r0] * (x[c0 * 4 + r1] * \
    x[c1 * 4 + r2] - x[c0 * 4 + r2] * x[c1 * 4 + r1]))



bool operator==(const mat4& lhs, const mat4& rhs)
{
    for (int i = 0; i < 16; i++)
    {
        if (fabsf(lhs.v[i] - rhs.v[i]) > MAT4_EPSILON)
        {
            return false;
        }
    }
    return true;
}

bool operator!=(const mat4& lhs, const mat4& rhs)
{
    return !(lhs == rhs);
}

mat4 operator+(const mat4& lhs, const mat4& rhs)
{
    return mat4{
        lhs.xx + rhs.xx, lhs.xy + rhs.xx, lhs.xz + rhs.xz, lhs.xw + rhs.xw,
        lhs.yx + rhs.yx, lhs.yy + rhs.yy, lhs.yz + rhs.yz, lhs.yw + rhs.yw,
        lhs.zx + rhs.zx, lhs.zy + rhs.zy, lhs.zz + rhs.zz, lhs.zw + rhs.zw,
        lhs.tx + rhs.tx, lhs.ty + rhs.ty, lhs.tz + rhs.tz, lhs.tw + rhs.tw
    };
}

// Scaling
mat4 operator*(const mat4& lhs, const float f)
{
    return mat4{
        lhs.xx * f, lhs.xy * f, lhs.xz * f, lhs.xw * f,
        lhs.yx * f, lhs.yy * f, lhs.yz * f, lhs.yw * f,
        lhs.zx * f, lhs.zy * f, lhs.zz * f, lhs.zz * f,
        lhs.tx * f, lhs.ty * f, lhs.tz * f, lhs.tw * f
    };
}

mat4 operator*(const mat4& a, const mat4& b)
{
    return mat4{
        M4D(0, 0), M4D(1, 0), M4D(2, 0), M4D(3, 0), // co0
        M4D(0, 1), M4D(1, 1), M4D(2, 1), M4D(3, 1), // co1
        M4D(0, 2), M4D(1, 2), M4D(2, 2), M4D(3, 2), // co2
        M4D(0, 3), M4D(1, 3), M4D(2, 3), M4D(3, 3), // co3
    };
}

vec4 operator*(const mat4& m, const vec4& v)
{
    return vec4{
        M4V4D(0, v.x, v.y, v.z, v.w),
        M4V4D(1, v.x, v.y, v.z, v.w),
        M4V4D(2, v.x, v.y, v.z, v.w),
        M4V4D(3, v.x, v.y, v.z, v.w),
    };
}

vec3 transformVector(const mat4& m, const vec3& v)
{
    return vec3{
        M4V4D(0, v.x, v.y, v.z, 0.0f),
        M4V4D(1, v.x, v.y, v.z, 0.0f),
        M4V4D(2, v.x, v.y, v.z, 0.0f),
    };
}

vec3 transformPoint(const mat4& m, const vec3& v, float& w)
{
    const float _w = w;
    w = M4V4D(0, v.x, v.y, v.z, _w);

    return vec3{
        M4V4D(0, v.x, v.y, v.z, _w),
        M4V4D(1, v.x, v.y, v.z, _w),
        M4V4D(2, v.x, v.y, v.z, _w),
    };
}

void transpose(mat4& m)
{
    M4SWAP(m.yx, m.xy)
    M4SWAP(m.zx, m.xz)
    M4SWAP(m.tx, m.xw)
    M4SWAP(m.zy, m.yz)
    M4SWAP(m.ty, m.yw)
    M4SWAP(m.tz, m.zw)
}

mat4 transposed(const mat4& m)
{
    return mat4{
        m.xx, m.yx, m.zx, m.tx,
        m.xy, m.yy, m.zy, m.ty,
        m.xz, m.yz, m.zz, m.tz,
        m.xw, m.yw, m.zw, m.tw,
    };
}

float determinant(const mat4& m)
{
    return m.v[0] * M4_3X3MINOR(m.v, 1, 2, 3, 1, 2, 3)
        - m.v[4] * M4_3X3MINOR(m.v, 0, 2, 3, 1, 2, 3)
        + m.v[8] * M4_3X3MINOR(m.v, 0, 1, 3, 1, 2, 3)
        - m.v[12] * M4_3X3MINOR(m.v, 0, 1, 2, 1, 2, 3);
}

mat4 adjugate(const mat4& m)
{
    // Cof (M[i,j]) = Minor(M[i,j] * pow(-1, i+j))
    mat4 cofactor;

    cofactor.v[0] = M4_3X3MINOR(m.v, 1, 2, 3, 1, 2, 3);
    cofactor.v[1] = -M4_3X3MINOR(m.v, 1, 2, 3, 0, 2, 3);
    cofactor.v[2] = M4_3X3MINOR(m.v, 1, 2, 3, 0, 1, 3);
    cofactor.v[3] = -M4_3X3MINOR(m.v, 1, 2, 3, 0, 1, 2);
    cofactor.v[4] = -M4_3X3MINOR(m.v, 0, 2, 3, 1, 2, 3);
    cofactor.v[5] = M4_3X3MINOR(m.v, 0, 2, 3, 0, 2, 3);
    cofactor.v[6] = -M4_3X3MINOR(m.v, 0, 2, 3, 0, 1, 3);
    cofactor.v[7] = M4_3X3MINOR(m.v, 0, 2, 3, 0, 1, 2);
    cofactor.v[8] = M4_3X3MINOR(m.v, 0, 1, 3, 1, 2, 3);
    cofactor.v[9] = -M4_3X3MINOR(m.v, 0, 1, 3, 0, 2, 3);
    cofactor.v[10] = M4_3X3MINOR(m.v, 0, 1, 3, 0, 1, 3);
    cofactor.v[11] = -M4_3X3MINOR(m.v, 0, 1, 3, 0, 1, 2);
    cofactor.v[12] = -M4_3X3MINOR(m.v, 0, 1, 2, 1, 2, 3);
    cofactor.v[13] = M4_3X3MINOR(m.v, 0, 1, 2, 0, 2, 3);
    cofactor.v[14] = -M4_3X3MINOR(m.v, 0, 1, 2, 0, 1, 3);
    cofactor.v[15] = M4_3X3MINOR(m.v, 0, 1, 2, 0, 1, 2);

    return transposed(cofactor);
}

mat4 inverse(const mat4& m)
{
    const float det = determinant(m);

    if (det == 0.0f)
    {
        std::cout << " Matrix determinant is 0\n";
        return mat4{};
    }

    const mat4 adj = adjugate(m);
    return adj * (1.0f / det);
}

void invert(mat4& m)
{
    const float det = determinant(m);
    if (det == 0.0f)
    {
        std::cout << " Matrix determinant is 0\n";
        m = mat4{};
        return;
    }
    m = adjugate(m) * (1.0f / det);
}