#pragma once

#include <string_view>

#include "Event.h"

namespace Combat::Event
{
    struct AbilityPreCast : public PreBase
    {

    };

    struct AbilityCast : public Base
    {

    };

    struct AbilityPreHit : public PreBase
    {

    };

    struct AbilityHit : public Base
    {

    };

    struct AbilityMiss : public Base
    {

    };
}
