#pragma once

#include <string>

#include "Event.h"
#include "Source.h"

#include "Ability.h"

namespace Combat::Ability
{
    template<class Entity, class Config>
    class Service
    {
    private:
        const Event::Bus<Entity, Config> &eventBus;

    public:
        explicit Service(const Event::Bus<Entity, Config> &eventBus);

    public:
        Snapshot<Entity> *PublishPreCastEvent(const std::string &ability, const Entity &caster) const;

        bool PublishHitEvents(const std::string &ability, const Entity &caster, const Entity &target) const;
    };
}
