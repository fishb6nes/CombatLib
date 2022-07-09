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
        bool PublishCastEvents(Ability::Snapshot &snapshot) const;

        bool PublishHitEvents(const Ability::Snapshot &snapshot) const;
    };
}
