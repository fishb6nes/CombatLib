#pragma once

#include <map>
#include <string_view>

#include "Event.h"

namespace Combat::Event
{
    struct AbilityPreCast : Cancellable
    {
        std::string_view ability;
        Source *caster;
    };

    struct AbilityCast
    {
        std::string_view ability;
        Source *caster;
    };

    struct AbilityPreHit : Cancellable
    {
        std::string_view ability;
        Source *caster;
        Source *target;
    };

    struct AbilityHit
    {
        std::string_view ability;
        Source *caster;
        Source *target;
    };

    struct AbilityMiss
    {
        std::string_view ability;
        Source *caster;
        Source *target;
    };
}
