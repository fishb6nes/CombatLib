#include "AbilityService.h"

#include "events.h"

using namespace Combat::Ability;

std::unique_ptr<Snapshot> Service::PublishPreCastEvent(
        std::string_view ability, Status::Affectable *caster) const
{
    Event::AbilityPreCast event {{ }, ability, caster };
    eventBus.PublishEvent(event);
    caster->GetCombatStatus().PublishEvent(event);
    return event.IsAllowed()
           ? std::make_unique<Snapshot>(std::move(event.modifiers))
           : nullptr;
}

bool Service::PublishHitEvents(
        std::string_view ability, Status::Affectable *caster, Status::Affectable *target) const
{
    Event::AbilityPreHit preEvent {{ }, ability, caster, target };
    caster->GetCombatStatus().PublishEvent(preEvent);
    target->GetCombatStatus().PublishEvent(preEvent);
    eventBus.PublishEvent(preEvent);
    if (preEvent.IsAllowed())
    {
        Event::AbilityHit hitEvent { preEvent.ability, caster, target };
        caster->GetCombatStatus().PublishEvent(hitEvent);
        target->GetCombatStatus().PublishEvent(hitEvent);
        eventBus.PublishEvent(hitEvent);
        return true;
    }
    else
    {
        Event::AbilityMiss missEvent { preEvent.ability, caster, target };
        caster->GetCombatStatus().PublishEvent(missEvent);
        target->GetCombatStatus().PublishEvent(missEvent);
        eventBus.PublishEvent(missEvent);
        return false;
    }
}
