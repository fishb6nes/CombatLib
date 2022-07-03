#include <cassert>

#include "AbilityService.h"

#include "events.h"

using namespace Combat::Ability;

std::unique_ptr<Snapshot> Service::PublishPreCastEvent(const std::string &ability, const Source &caster) const
{
    assert(caster.status != nullptr && "Combat::Source with null status cannot cast abilities");

    Event::AbilityPreCast event {{ }, ability, caster };
    eventBus.PublishEvent(event);
    caster.status->PublishEvent(event);
    return event.IsAllowed()
           ? std::make_unique<Snapshot>(std::move(event.modifiers))
           : nullptr;
}

bool Service::PublishHitEvents(const std::string &ability, const Source &caster, const Source &target) const
{
    assert(caster.status != nullptr && "Combat::Source with null status cannot cast abilities");
    assert(target.status != nullptr && "Combat::Source with null status cannot be targeted by abilities");

    Event::AbilityPreHit preEvent {{ }, ability, caster, target };
    caster.status->PublishEvent(preEvent);
    target.status->PublishEvent(preEvent);
    eventBus.PublishEvent(preEvent);
    if (preEvent.IsAllowed())
    {
        Event::AbilityHit hitEvent { preEvent.ability, caster, target };
        caster.status->PublishEvent(hitEvent);
        target.status->PublishEvent(hitEvent);
        eventBus.PublishEvent(hitEvent);
        return true;
    }
    else
    {
        Event::AbilityMiss missEvent { preEvent.ability, caster, target };
        caster.status->PublishEvent(missEvent);
        target.status->PublishEvent(missEvent);
        eventBus.PublishEvent(missEvent);
        return false;
    }
}
