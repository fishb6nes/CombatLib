#pragma once

#include "../Entity/Hittable.h"

namespace Combat
{
    class BasicHitbox
    {
    public:
        bool
        Test(Hittable auto hittable)
        {
            return false;
        }
    };
}
