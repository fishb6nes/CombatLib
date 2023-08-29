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
    };
}
