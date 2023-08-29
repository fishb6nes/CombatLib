#pragma once

#include <vector>

#include "Entity.h"

namespace Combat
{
    class EntityService
    {
    public:
        virtual std::vector<Entity>
        GetNearbyEntities(float3 location) = 0;
    };
}
