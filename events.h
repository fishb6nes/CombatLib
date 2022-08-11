#pragma once

#include <string_view>

#include "Ability.h"
#include "Event.h"

namespace Combat
{
    class Entity;

    namespace Event
    {
        struct AbilityPreCast : PreBase
        {
            std::string_view ability;
            Entity &caster;
            Ability::Modifiers modifiers { };

            AbilityPreCast(std::string_view ability, Entity &caster)
                    : PreBase { }, ability { ability }, caster { caster } { }
        };

        struct AbilityCast : Base
        {
            std::string_view ability;
            Entity &caster;

            AbilityCast(std::string_view ability, Entity &caster)
                    : Base { }, ability { ability }, caster { caster } { }
        };

        struct AbilityPreHit : PreBase
        {
            std::string_view ability;
            Entity &caster;
            Entity &target;

            AbilityPreHit(std::string_view ability, Entity &caster, Entity &target)
                    : PreBase { }, ability { ability }, caster { caster }, target { target } { }
        };

        struct AbilityHit : Base
        {
            std::string_view ability;
            Entity &caster;
            Entity &target;

            AbilityHit(std::string_view ability, Entity &caster, Entity &target)
                    : Base { }, ability { ability }, caster { caster }, target { target } { }
        };

        struct AbilityMiss : Base
        {
            std::string_view ability;
            Entity &caster;
            Entity &target;

            AbilityMiss(std::string_view ability, Entity &caster, Entity &target)
                    : Base { }, ability { ability }, caster { caster }, target { target } { }
        };
    }
}
