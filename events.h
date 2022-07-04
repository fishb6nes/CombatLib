#pragma once

#include <map>
#include <string>

#include "Event.h"
#include "Modifier.h"

namespace Combat::Event
{
    struct AbilityPreCast : public Cancellable
    {
        std::string ability;
        Source *caster;
    };

    struct AbilityCast
    {
        std::string ability;
        Source *caster;
    };

    struct AbilityPreHit : public Cancellable
    {
        std::string ability;
        Source *caster;
        Source *target;
    };

    struct AbilityHit
    {
        std::string ability;
        Source *caster;
        Source *target;
    };

    struct AbilityMiss
    {
        std::string ability;
        Source *caster;
        Source *target;
    };
}