#pragma once

#include <optional>
#include <string_view>

#include "Ability.h"
#include "Event.h"
#include "Entity.h"

namespace Combat::Ability
{
    class Service
    {
    private:
        Event::Bus &eventBus;

    public:
        explicit Service(Event::Bus &eventBus)
                : eventBus { eventBus } { }

    public:
        std::optional<Ability::Modifiers> PublishCastEvents(
                std::string_view name, Entity &caster) const;

        bool PublishHitEvents(
                std::string_view name, Entity &caster, Entity &target) const;
    };
}
