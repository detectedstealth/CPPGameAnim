#include <cmath>

#include "mat4.h"

#define M4D(aRow, bCol) \
    a.v[0 * 4 + aRow] * b.v[bCol * 4 + 0] + \
    a.v[1 * 4 + aRow] * b.v[bCol * 4 + 1] + \
    a.v[2 * 4 + aRow] * b.v[bCol * 4 + 2] + \
    a.v[3 * 4 + aRow] * b.v[bCol * 4 + 3]

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