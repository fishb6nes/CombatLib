#pragma once

#include "../concepts.h"
#include "../Entity/Entity.h"
#include "../Entity/Hittable.h"

#include "Hitbox/BasicHitbox.h"
#include "Hitbox/CachedHitbox.h"
#include "Hitbox/TargetedHitbox.h"

namespace Combat
{
    template<typename T, typename U>
    concept Hitbox = requires(T hitbox, U hittable)
    {
        { hittable.GetLocation() } -> std::same_as<float3>;
        { hittable.GetVolume() } -> same_as_any<aabb, sphere>;

        { hitbox.Test(hittable) } -> std::same_as<bool>;
    };

    static_assert(Hitbox<BasicHitbox, Entity>);
    static_assert(Hitbox<CachedHitbox>);
    static_assert(Hitbox<TargetedHitbox>);
}
