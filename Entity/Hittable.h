#pragma once

#include "../concepts.h"
#include "../math.h"

namespace Combat
{
    template<typename T>
    concept Hittable = requires(T hittable)
    {
        { hittable.GetLocation() } -> std::same_as<float3>;
        { hittable.GetVolume() } -> same_as_any<aabb, sphere>;
    };
}
