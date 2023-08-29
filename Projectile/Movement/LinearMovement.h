#pragma once

#include "../../math.h"

namespace Combat
{
    struct LinearMovement
    {
        float3 location;
        bool hasNext;

        float3 origin;
        float3 velocity;
        float maxRange;

        inline static bool
        HasNext(const LinearMovement &it)
        {
            return it.hasNext;
        }

        inline static LinearMovement
        SetNext(const LinearMovement &it)
        {
            auto [location, hasNext, origin, velocity, maxRange] = it;

            float distance = (location - origin).length();
            float distanceDelta = velocity.length();
            float nextDistance = distance + distanceDelta;
            if (nextDistance < maxRange)
            {
                location = location + velocity;
            }
            else
            {
                float deltaCorrection = (nextDistance - maxRange) / distanceDelta;
                location = location + (velocity * deltaCorrection);
                hasNext = false;
            }
            return { location, hasNext, origin, velocity, maxRange };
        }
    };
}
