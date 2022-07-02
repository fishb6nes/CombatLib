#pragma once

#include <string>

#include "Ability.h"
#include "Event.h"

namespace Combat::Ability
{
    class Service
    {
    private:
        const Event::Bus &eventBus;

    public:
        explicit Service(const Event::Bus &eventBus) : eventBus { eventBus } { }

    public:
        Snapshot *PublishPreCastEvent(const std::string &ability, const Source &caster) const;

        bool PublishHitEvents(const std::string &ability, const Source &caster, const Source &target) const;
    };
}
