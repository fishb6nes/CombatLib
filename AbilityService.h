#pragma once

#include <string>

#include "Event.h"
#include "Source.h"

#include "Ability.h"

namespace Combat::Ability
{
    template<class AbilityAttribute, class Entity>
    class Service
    {
    private:
        const Event::Bus<AbilityAttribute, Entity> &eventBus;

    public:
        explicit Service(const Event::Bus<AbilityAttribute, Entity> &eventBus);

    public:
        Snapshot<Entity> *PublishPreCastEvent(const std::string &ability, const Entity &caster) const;

        bool PublishHitEvents(const std::string &ability, const Entity &caster, const Entity &target) const;
    };
}
