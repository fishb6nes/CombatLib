#pragma once

#include <vector>

#include "./math.h"
#include "Entity.h"

namespace Combat
{
    class EntityService
    {
        virtual std::vector<Combat::Entity> GetNearbyEntities(float3 location, float radius) = 0;
    };
}
