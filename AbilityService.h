#pragma once

#include <string>

#include "Ability.h"
#include "Event.h"
#include "Status.h"

namespace Combat::Ability
{
    class Service
    {
    private:
        const Event::Bus &eventBus;

    public:
        explicit Service(const Event::Bus &eventBus)
                : eventBus { eventBus } { }

    public:
        std::unique_ptr<Snapshot> PublishPreCastEvent(
                const std::string &ability, Status::Affectable *caster) const;

        bool PublishHitEvents(
                const std::string &ability, Status::Affectable *caster, Status::Affectable *target) const;
    };
}
