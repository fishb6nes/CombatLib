#pragma once

#include <vector>

#include "./math.h"
#include "Status.h"

namespace Combat
{
    class EntityService
    {
        virtual std::vector<Combat::Status::Affectable> GetNearbyEntities(float3 location, float radius) = 0;
    };
}
