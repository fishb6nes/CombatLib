#include "AbilityService.h"

#include "events.h"
#include "Entity.h"

using namespace Combat;

std::optional<AbilityModifiers> AbilityService::PublishCastEvents(std::string_view name, Entity &caster) const
{
    Event::AbilityPreCastEvent preEvent { name, caster };
    caster.GetCombatStatus().PublishPreEvent(preEvent);
    eventBus.PublishPreEvent(preEvent);

    if (preEvent.IsAllowed())
    {
        Event::AbilityCastEvent event { name, caster };
        caster.GetCombatStatus().PublishEvent(event);
        eventBus.PublishEvent(event);

        return std::make_optional(std::move(preEvent.modifiers));
    }
    else return std::nullopt;
}

bool AbilityService::PublishHitEvents(std::string_view name, Entity &caster, Entity &target) const
{
    Event::AbilityPreHitEvent preEvent { name, caster, target };
    caster.GetCombatStatus().PublishPreEvent(preEvent);
    target.GetCombatStatus().PublishPreEvent(preEvent);
    eventBus.PublishPreEvent(preEvent);

    if (preEvent.IsAllowed())
    {
        Event::AbilityHit hitEvent { name, caster, target };
        caster.GetCombatStatus().PublishEvent(hitEvent);
        target.GetCombatStatus().PublishEvent(hitEvent);
        eventBus.PublishEvent(hitEvent);

        return true;
    }
    else
    {
        Event::AbilityMiss missEvent { name, caster, target };
        caster.GetCombatStatus().PublishEvent(missEvent);
        target.GetCombatStatus().PublishEvent(missEvent);
        eventBus.PublishEvent(missEvent);

        return false;
    }
}
