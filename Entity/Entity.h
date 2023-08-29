#pragma once

#include "../math.h"
#include "../Ability/Hitbox.h"
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
        Hitbox hitbox;
        EventBus status;

    public:
        Entity(std::string_view name, int id, float3 location, Hitbox hitbox, int type = COMBAT_ENTITY_TYPE)
                : Source(type, name), id { id }, location { location }, hitbox { hitbox } { }

        inline int
        GetCombatId() const { return id; }

        inline float3
        GetLocation() const { return location; }

        inline Hitbox
        GetHitbox() const { return hitbox; }

        inline EventBus &
        GetCombatStatus() { return status; }
    };
}
