#pragma once

#include <string_view>

#include "Event.h"

namespace Combat::Event
{
    struct AbilityPreCast : PreBase
    {
        std::string_view ability;
        Source *caster;
    };

    struct AbilityCast : Base
    {
        std::string_view ability;
        Source *caster;
    };

    struct AbilityPreHit : PreBase
    {
        std::string_view ability;
        Source *caster;
        Source *target;
    };

    struct AbilityHit : Base
    {
        std::string_view ability;
        Source *caster;
        Source *target;
    };

    struct AbilityMiss : Base
    {
        std::string_view ability;
        Source *caster;
        Source *target;
    };
}
