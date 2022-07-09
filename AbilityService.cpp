#include "AbilityService.h"

#include "events.h"

using namespace Combat::Ability;

bool Service::PublishCastEvents(Ability::Snapshot &snapshot) const
{
    Event::AbilityPreCast preEvent { snapshot };
    snapshot.caster.GetCombatStatus().PublishPreEvent(preEvent);
    eventBus.PublishPreEvent(preEvent);

    if (preEvent.IsAllowed())
    {
        snapshot.modifiers = std::move(preEvent.modifiers);

        Event::AbilityCast event { snapshot };
        snapshot.caster.GetCombatStatus().PublishEvent(event);
        eventBus.PublishEvent(event);

        return true;
    }
    else return false;
}

bool Service::PublishHitEvents(const Ability::Snapshot &snapshot) const
{
    Event::AbilityPreHit preEvent { snapshot };
    snapshot.caster.GetCombatStatus().PublishPreEvent(preEvent);
    snapshot.target->GetCombatStatus().PublishPreEvent(preEvent);
    eventBus.PublishPreEvent(preEvent);

    if (preEvent.IsAllowed())
    {
        Event::AbilityHit hitEvent { snapshot };
        snapshot.caster.GetCombatStatus().PublishEvent(hitEvent);
        snapshot.target->GetCombatStatus().PublishEvent(hitEvent);
        eventBus.PublishEvent(hitEvent);

        return true;
    }
    else
    {
        Event::AbilityMiss missEvent { snapshot };
        snapshot.GetCaster().GetCombatStatus().PublishEvent(missEvent);
        snapshot.GetTarget()->GetCombatStatus().PublishEvent(missEvent);
        eventBus.PublishEvent(missEvent);

        return false;
    }
}
