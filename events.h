#pragma once

#include <string_view>

#include "Ability.h"
#include "Event.h"

namespace Combat
{
    class Entity;

    struct AbilityPreCastEvent : PreEvent
    {
        std::string_view ability;
        Entity &caster;
        Ability::Modifiers modifiers;

        AbilityPreCastEvent(std::string_view ability, Entity &caster)
                : PreEvent { }, ability { ability }, caster { caster } { }
    };

    struct AbilityCastEvent : Event
    {
        std::string_view ability;
        Entity &caster;

        AbilityCastEvent(std::string_view ability, Entity &caster)
                : Event { }, ability { ability }, caster { caster } { }
    };

    struct AbilityPreHitEvent : PreEvent
    {
        std::string_view ability;
        Entity &caster;
        Entity &target;

        AbilityPreHitEvent(std::string_view ability, Entity &caster, Entity &target)
                : PreEvent { }, ability { ability }, caster { caster }, target { target } { }
    };

    struct AbilityHitEvent : Event
    {
        std::string_view ability;
        Entity &caster;
        Entity &target;

        AbilityHitEvent(std::string_view ability, Entity &caster, Entity &target)
                : Event { }, ability { ability }, caster { caster }, target { target } { }
    };

    struct AbilityMissEvent : Event
    {
        std::string_view ability;
        Entity &caster;
        Entity &target;

        AbilityMissEvent(std::string_view ability, Entity &caster, Entity &target)
                : Event { }, ability { ability }, caster { caster }, target { target } { }
    };
}
