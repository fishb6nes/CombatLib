#pragma once

#include "../../math.h"

namespace Combat
{
    struct AABBHitbox;
}

namespace Combat
{
    struct SphereHitbox
    {
        float3 center;
        float radius;

        static SphereHitbox
        Translate(const SphereHitbox &it, float3 translation);

        static bool
        TestAABB(const SphereHitbox &it, const AABBHitbox &other);

        static bool
        TestSphere(const SphereHitbox &it, const SphereHitbox &other);
    };
}
