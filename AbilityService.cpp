#include "AbilityService.h"

using namespace Combat;
using namespace Combat::Ability;

template<class Entity, class Config>
Service<Entity, Config>::Service(const Event::Bus<Entity, Config> &eventBus)
        : eventBus { eventBus }
{
}

template<class Entity, class Config>
Snapshot<Entity> *Service<Entity, Config>::PublishPreCastEvent(
        const std::string &ability, const Entity &caster) const
{
    Event::AbilityPreCast<Entity, Config> event {{ }, ability, caster };
    eventBus.PublishEvent(event);
    caster.status.PublishEvent(event);
    if (event.IsAllowed())
    {
        Source source { &caster, event.ability };
        // val modifiers = preCastEvent.modifiers
        // new AbilitySnapshot(source, config, modifiers) |> Some.apply
        return nullptr;
    }
    return nullptr;
}

template<class Entity, class Config>
bool Service<Entity, Config>::PublishHitEvents(
        const std::string &ability, const Entity &caster, const Entity &target) const
{
    Event::AbilityPreHit<Entity, Config> preEvent {{ }, ability, caster, target };
    caster.status.PublishEvent(preEvent);
    target.status.PublishEvent(preEvent);
    eventBus.PublishEvent(preEvent);
    if (preEvent.IsAllowed())
    {
        Event::AbilityHit<Entity> hitEvent { preEvent.ability, caster, target };
        caster.status.PublishEvent(hitEvent);
        target.status.PublishEvent(hitEvent);
        eventBus.PublishEvent(hitEvent);
        return true;
    }
    else
    {
        Event::AbilityMiss<Entity> missEvent { preEvent.ability, caster, target };
        caster.status.PublishEvent(missEvent);
        target.status.PublishEvent(missEvent);
        eventBus.PublishEvent(missEvent);
        return false;
    }
}
