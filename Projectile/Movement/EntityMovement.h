#pragma once

#include "../../math.h"

namespace Combat
{
    struct EntityMovement
    {
        float3 location;

        Entity *entity; // TODO use entityId in stead?

        inline static bool
        HasNext(const EntityMovement &it)
        {
            return true; // TODO check if entity is alive
        }

        inline static EntityMovement
        SetNext(const EntityMovement &it)
        {
            return { it.entity->GetLocation(), it.entity };
        }
    };
}
