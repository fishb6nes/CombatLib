#pragma once

#include <cmath>

namespace Combat
{
    struct float3
    {
        float x, y, z;

        inline float3
        operator+(const float3 &other) const
        {
            return { x + other.x,
                     y + other.y,
                     z + other.z };
        }

        inline float3
        operator-(const float3 &other) const
        {
            return { x - other.x,
                     y - other.y,
                     z - other.z };
        }

        inline float3
        operator-() const
        {
            return { -x, -y, -z };
        }

        inline float3
        operator*(const float &scalar) const
        {
            return { x * scalar,
                     y * scalar,
                     z * scalar };
        }

        inline float3
        operator/(const float &scalar) const
        {
            return { x / scalar,
                     y / scalar,
                     z / scalar };
        }

        inline float
        length() const
        {
            return sqrt(x * x + y * y + z * z);
        }

        inline float3
        normalized() const
        {
            return *this / length();
        }
    };

    struct capsule
    {
        float3 a, b;
        float radius;

        inline capsule
        operator+(float3 translation) const
        {
            return { a + translation, b + translation, radius };
        }

        inline capsule
        operator-(float3 translation) const
        {
            return { a - translation, b - translation, radius };
        }

        inline capsule
        operator*(float scalar) const
        {
            return { a, b, radius * scalar };
        }

        inline capsule
        operator/(float scalar) const
        {
            return { a, b, radius / scalar };
        }
    };

    struct sphere
    {
        float3 center;
        float radius;

        inline sphere
        operator+(float3 translation) const
        {
            return { center + translation, radius };
        }

        inline sphere
        operator-(float3 translation) const
        {
            return { center - translation, radius };
        }

        inline sphere
        operator*(float scalar) const
        {
            return { center, radius * scalar };
        }

        inline sphere
        operator/(float scalar) const
        {
            return { center, radius / scalar };
        }

        inline bool
        test(const capsule &it) const
        {
            auto ab = it.b - it.a;
            auto ac = center - it.a;
            float abLengthSquared = ab.x * ab.x + ab.y * ab.y + ab.z * ab.z;
            float t = (ac.x * ab.x + ac.y * ab.y + ac.z * ab.z) / abLengthSquared;

            return test(sphere { it.a + ab * t, it.radius });
        }

        inline bool
        test(const sphere &it) const
        {
            float3 distance = center - it.center;
            return distance.length() < (radius + it.radius);
        }
    };
}
