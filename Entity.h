#pragma once

#include <string_view>
#include <vector>

#include "./math.h"
#include "Event.h"
#include "Source.h"

namespace Combat
{
    class Entity : public Source
    {
    private:
        int id;
        EventBus status { };

    public:
        Entity(int type, std::string_view name, Source *parent, int id)
                : Source(type, name, parent), id { id } { }

        inline int GetCombatId() const { return id; }

        inline EventBus &GetCombatStatus() { return status; }
    };


    class EntityService
    {
        virtual std::vector<Entity> GetNearbyEntities(float3 location, float radius) = 0;
    };
}
