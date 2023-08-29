#pragma once

#include "../../math.h"

namespace Combat
{
    struct OneOffMovement
    {
        float3 location;
        bool hasNext;

        inline static bool
        HasNext(const OneOffMovement &it)
        {
            return it.hasNext;
        }

        inline static OneOffMovement
        SetNext(const OneOffMovement &it)
        {
            return { it.location, false };
        }
    };
}
