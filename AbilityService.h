#pragma once

#include <optional>
#include <string_view>

#include "Ability.h"
#include "Event.h"
#include "Entity.h"

namespace Combat
{
    class AbilityService
    {
    private:
        Event::EventBus &eventBus;

    public:
        explicit AbilityService(Event::EventBus &eventBus)
                : eventBus { eventBus } { }

    public:
        std::optional<AbilityModifiers> PublishCastEvents(std::string_view name, Entity &caster) const;

        bool PublishHitEvents(std::string_view name, Entity &caster, Entity &target) const;
    };
}
