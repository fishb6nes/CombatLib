#pragma once

#include <cmath>

namespace Combat
{
    struct float3
    {
        float x, y, z;

        float3
        operator*(const float &scalar) const
        {
            return { x * scalar,
                     y * scalar,
                     z * scalar };
        }

        float3
        operator/(const float &scalar) const
        {
            return { x / scalar,
                     y / scalar,
                     z / scalar };
        }

        float3
        operator+(const float3 &other) const
        {
            return { x + other.x,
                     y + other.y,
                     z + other.z };
        }

        float3
        operator-(const float3 &other) const
        {
            return { x - other.x,
                     y - other.y,
                     z - other.z };
        }

        float
        length() const
        {
            return sqrt(x * x + y * y + z * z);
        }

        float3
        normalized() const
        {
            return *this / length();
        }
    };
}
