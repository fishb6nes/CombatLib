#pragma once

#include <vector>

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
        T hitbox;
        V movement;
    };
}
