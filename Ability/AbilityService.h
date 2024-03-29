#pragma once

#include <optional>

namespace Combat
{
    class Ability;
    class Entity;
}

namespace Combat
{
    class AbilityService
    {
    private:
        EventBus &eventBus;

    public:
        explicit AbilityService(EventBus &eventBus)
                : eventBus { eventBus } { }

    public:
        std::optional<Ability::Modifiers>
        PublishCastEvents(std::string_view ability, Entity &caster) const;

        bool
        PublishHitEvents(Ability &ability, Entity &target) const;
    };
}
