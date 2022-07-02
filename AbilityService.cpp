#include "AbilityService.h"

using namespace Combat;
using namespace Combat::Ability;

template<class AbilityAttribute, class Entity>
Service<AbilityAttribute, Entity>::Service(const Event::Bus<AbilityAttribute, Entity> &eventBus)
        : eventBus { eventBus }
{
}

template<class AbilityAttribute, class Entity>
Snapshot<Entity> *Service<AbilityAttribute, Entity>::PublishPreCastEvent(
        const std::string &ability, const Entity &caster) const
{
    Event::AbilityPreCast<AbilityAttribute, Entity> event {{ }, ability, caster };
    eventBus.PublishEvent(event);
    caster.status.PublishEvent(event);
    if (event.IsAllowed())
    {
        Source source { &caster, event.ability };
        // val modifiers = preCastEvent.modifiers
        // new AbilitySnapshot(source, config, modifiers) |> Some.apply
        return nullptr;
    }
    else return nullptr;
}

template<class AbilityAttribute, class Entity>
bool Service<AbilityAttribute, Entity>::PublishHitEvents(
        const std::string &ability, const Entity &caster, const Entity &target) const
{
    Event::AbilityPreHit<AbilityAttribute, Entity> preEvent {{ }, ability, caster, target };
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
