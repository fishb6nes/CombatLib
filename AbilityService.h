#pragma once

#include <string_view>

#include "Ability.h"
#include "Event.h"
#include "Status.h"

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
        std::unique_ptr<Snapshot> PublishPreCastEvent(
                std::string_view ability, Status::Affectable *caster) const;

        bool PublishHitEvents(
                std::string_view ability, Status::Affectable *caster, Status::Affectable *target) const;
    };
}
