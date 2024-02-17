#pragma once

#include "../math.h"
#include "../Core/Source.h"
#include "../Event/EventBus.h"

#ifndef COMBAT_ENTITY_TYPE
#define COMBAT_ENTITY_TYPE 0
#endif

namespace Combat
{
    class Entity : public Source
    {
    private:
        int id;
        float3 location;
        sphere volume;
        EventBus status;

    public:
        Entity(std::string_view name, int id, float3 location, int type = COMBAT_ENTITY_TYPE)
                : Source(type, name), id { id }, location { location } { }

        inline int
        GetCombatId() const { return id; }

        inline float3
        GetLocation() const { return location; }

        inline sphere
        GetVolume() const { return volume; }

        inline EventBus &
        GetCombatStatus() { return status; }
    };
}
