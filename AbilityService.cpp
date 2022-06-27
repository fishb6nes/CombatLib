#include "AbilityService.h"

using namespace Combat;
using namespace Combat::Ability;

template<class Entity, class Attribute>
Service<Entity, Attribute>::Service(const Event::Bus<Entity, Attribute> &eventBus)
        : eventBus { eventBus }
{
}

template<class Entity, class Attribute>
Snapshot *Service<Entity, Attribute>::PublishPreCastEvent(
        std::string *const ability, Entity *const caster) const
{
    Event::AbilityPreCast<Entity, Attribute> event { ability, caster };
    event = eventBus.PublishEvent(event);
    event = caster.status.PublishEvent(event);
    if (event.isExplicitlyAllowed || !event.isCancelled)
    {
        Source source { std::move(event.ability), caster.id };
        // val modifiers = preCastEvent.modifiers
        // new AbilitySnapshot(source, config, modifiers) |> Some.apply
        return nullptr;
    }
    return nullptr;
}

template<class Entity, class Attribute>
bool Service<Entity, Attribute>::PublishHitEvents(
        std::string ability, const Entity &caster, const Entity &target) const
{
    Event::AbilityPreHit<Entity, Attribute> preEvent { std::move(ability), caster, target };
    preEvent = caster.status.PublishEvent(preEvent);
    preEvent = target.status.PublishEvent(preEvent);
    preEvent = eventBus.PublishEvent(preEvent);
    if (preEvent.isExplicitlyAllowed || !preEvent.isCancelled)
    {
        Event::AbilityHit<Entity> event { std::move(preEvent.ability), caster, target };
        event = caster.status.PublishEvent(event);
        event = target.status.PublishEvent(event);
        eventBus.PublishEvent(event);
        return true;
    }
    else
    {
        Event::AbilityMiss<Entity> event { std::move(preEvent.ability), caster, target };
        event = caster.status.PublishEvent(event);
        event = target.status.PublishEvent(event);
        eventBus.PublishEvent(event);
        return false;
    }
}
