#pragma once

#include <string_view>
#include <vector>

#include "./math.h"
#include "EventBus.h"
#include "Source.h"

#ifndef COMBAT_ENTITY_TYPE
#define COMBAT_ENTITY_TYPE 0
#endif

namespace Combat
{
    class Entity : public Source
    {
    private:
        int id;
        EventBus status;

    public:
        Entity(std::string_view name, int id, int type = COMBAT_ENTITY_TYPE)
                : Source(type, name), id { id } { }

        inline int GetCombatId() const { return id; }

        inline EventBus &GetCombatStatus() { return status; }
    };

    class EntityService
    {
        virtual std::vector<Entity> GetNearbyEntities(float3 location, float radius) = 0;
    };
}
