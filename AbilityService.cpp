#include "AbilityService.h"

#include "events.h"

using namespace Combat::Ability;

std::unique_ptr<Snapshot> Service::PublishPreCastEvent(
        const std::string &ability, Status::Affectable *caster) const
{
    Event::AbilityPreCast event {{ }, ability, caster };
    eventBus.PublishEvent(event);
    caster->GetStatus().PublishEvent(event);
    return event.IsAllowed()
           ? std::make_unique<Snapshot>(std::move(event.modifiers))
           : nullptr;
}

bool Service::PublishHitEvents(
        const std::string &ability, Status::Affectable *caster, Status::Affectable *target) const
{
    Event::AbilityPreHit preEvent {{ }, ability, caster, target };
    caster->GetStatus().PublishEvent(preEvent);
    target->GetStatus().PublishEvent(preEvent);
    eventBus.PublishEvent(preEvent);
    if (preEvent.IsAllowed())
    {
        Event::AbilityHit hitEvent { preEvent.ability, caster, target };
        caster->GetStatus().PublishEvent(hitEvent);
        target->GetStatus().PublishEvent(hitEvent);
        eventBus.PublishEvent(hitEvent);
        return true;
    }
    else
    {
        Event::AbilityMiss missEvent { preEvent.ability, caster, target };
        caster->GetStatus().PublishEvent(missEvent);
        target->GetStatus().PublishEvent(missEvent);
        eventBus.PublishEvent(missEvent);
        return false;
    }
}
