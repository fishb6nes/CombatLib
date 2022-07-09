#pragma once

#include <string_view>

#include "Ability.h"
#include "Event.h"

namespace Combat
{
    namespace Status
    {
        class Affectable;
    }

    namespace Event
    {
        struct AbilityPreCast : PreBase
        {
            std::string_view ability;
            Status::Affectable &caster;
            Ability::Modifiers modifiers { };

            AbilityPreCast(std::string_view ability, Status::Affectable &caster)
                    : PreBase { }, ability { ability }, caster { caster } { }
        };

        struct AbilityCast : Base
        {
            std::string_view ability;
            Status::Affectable &caster;

            AbilityCast(std::string_view ability, Status::Affectable &caster)
                    : Base { }, ability { ability }, caster { caster } { }
        };

        struct AbilityPreHit : PreBase
        {
            std::string_view ability;
            Status::Affectable &caster;
            Status::Affectable &target;

            AbilityPreHit(std::string_view ability, Status::Affectable &caster, Status::Affectable &target)
                    : PreBase { }, ability { ability }, caster { caster }, target { target } { }
        };

        struct AbilityHit : Base
        {
            std::string_view ability;
            Status::Affectable &caster;
            Status::Affectable &target;

            AbilityHit(std::string_view ability, Status::Affectable &caster, Status::Affectable &target)
                    : Base { }, ability { ability }, caster { caster }, target { target } { }
        };

        struct AbilityMiss : Base
        {
            std::string_view ability;
            Status::Affectable &caster;
            Status::Affectable &target;

            AbilityMiss(std::string_view ability, Status::Affectable &caster, Status::Affectable &target)
                    : Base { }, ability { ability }, caster { caster }, target { target } { }
        };
    }
}
