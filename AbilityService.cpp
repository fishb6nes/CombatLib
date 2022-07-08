#include "AbilityService.h"

#include "events.h"

using namespace Combat::Ability;

std::unique_ptr<Snapshot> Service::PublishPreCastEvent(
        std::string_view ability, Status::Affectable *caster) const
{
    Event::AbilityPreCast event {{ }, ability, caster };
    eventBus.PublishPreEvent(event);
    caster->GetCombatStatus().PublishPreEvent(event);
    return event.IsAllowed()
           ? std::make_unique<Snapshot>(std::move(event.modifiers))
           : nullptr;
}

bool Service::PublishHitEvents(
        std::string_view ability, Status::Affectable *caster, Status::Affectable *target) const
{
    Event::AbilityPreHit preEvent {{ }, ability, caster, target };
    caster->GetCombatStatus().PublishPreEvent(preEvent);
    target->GetCombatStatus().PublishPreEvent(preEvent);
    eventBus.PublishPreEvent(preEvent);
    if (preEvent.IsAllowed())
    {
        Event::AbilityHit hitEvent {{ }, ability, caster, target };
        caster->GetCombatStatus().PublishEvent(hitEvent);
        target->GetCombatStatus().PublishEvent(hitEvent);
        eventBus.PublishEvent(hitEvent);
        return true;
    }
    else
    {
        Event::AbilityMiss missEvent {{ }, ability, caster, target };
        caster->GetCombatStatus().PublishEvent(missEvent);
        target->GetCombatStatus().PublishEvent(missEvent);
        eventBus.PublishEvent(missEvent);
        return false;
    }
}
