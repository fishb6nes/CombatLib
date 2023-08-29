#pragma once

#include "../Ability/Hitbox.h"

#include "Movement.h"

namespace Combat
{
    class Ability;
}

namespace Combat
{
    struct Projectile
    {
        Ability *ability;
        Hitbox hitbox;
        Movement movement;

        static bool
        CollideEntities(const Projectile &it, float3 origin, float3 target);

        static bool
        CollideWorld(const Projectile &it, float3 origin, float3 target);
    };
}
