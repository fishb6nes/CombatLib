#pragma once

#include "../../math.h"

namespace Combat
{
    struct StaticMovement
    {
        float3 location;

        inline static bool
        HasNext(const StaticMovement &_)
        {
            return true;
        }

        inline static StaticMovement
        SetNext(const StaticMovement &it)
        {
            return it;
        }
    };
}
