#pragma once

#include <vector>

namespace Combat
{
    class Entity;

    struct float3;
}

namespace Combat
{
    class EntityService
    {
        virtual std::vector<Entity> GetNearbyEntities(float3 location, float radius) = 0;
    };
}
