#pragma once

#include "../../math.h"

namespace Combat
{
    struct SphereHitbox;
}

namespace Combat
{
    struct AABBHitbox
    {
        float3 min, max;
        float dx, dy, dz;

        AABBHitbox(float3 min, float3 max)
                : min { min }, max { max }
        {
            dx = max.x - min.x;
            dy = max.y - min.y;
            dz = max.z - min.z;
        }

        static AABBHitbox
        Translate(const AABBHitbox &it, float3 translation);

        static bool
        TestAABB(const AABBHitbox &it, const AABBHitbox &other);

        static bool
        TestSphere(const AABBHitbox &it, const SphereHitbox &other);
    };
}
