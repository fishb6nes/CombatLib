#include <cassert>

#include "AbilityService.h"

#include "events.h"

using namespace Combat::Ability;

Snapshot *Service::PublishPreCastEvent(const std::string &ability, const Source &caster) const
{
    assert(caster.status != nullptr);

    Event::AbilityPreCast event {{ }, ability, caster };
    eventBus.PublishEvent(event);
    caster.status->PublishEvent(event);
    if (event.IsAllowed())
    {
        // Source source { &caster, event.ability };
        // val modifiers = preCastEvent.modifiers
        // new AbilitySnapshot(source, config, modifiers) |> Some.apply
        return nullptr;
    }
    else return nullptr;
}

bool Service::PublishHitEvents(const std::string &ability, const Source &caster, const Source &target) const
{
    assert(caster.status != nullptr);
    assert(target.status != nullptr);

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
