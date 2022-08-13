#include "Projectile.h"

#include "Ability.h"
#include "AbilityService.h"
#include "Hitbox.h"
#include "Movement.h"

using namespace Combat;

bool Projectile::Update(AbilityService &abilityService, EntityService &entityService)
{
    bool remove = false;
    float3 origin = movement.Get();
    if (movement.HasNext())
    {
        float3 target = movement.Next();
        remove |= TestEntityCollisions(origin, target, abilityService, entityService)
                  || TestWorldCollisions(origin, target);
    }
    else
    {
        ability.OnProjectileOutOfRange(*this);
        remove = true;
    }
    return remove;
}

bool Projectile::TestEntityCollisions(float3 origin, float3 target,
                                      AbilityService &abilityService, EntityService &entityService)
{
    bool remove = false;
    auto collisions = hitbox.GetEntityCollisions(origin, target, entityService);
    for (Entity *collision : collisions)
    {
        Entity &entity = *collision;

        if (entitiesHit.find(entity.GetCombatId()) != entitiesHit.end())
        {
            // save entity regardless of whether hit event succeeds as otherwise
            // it'd come right back next tick and not count as a proper miss
            entitiesHit.insert(entity.GetCombatId());
            remove |= abilityService.PublishHitEvents(ability, entity)
                      ? ability.OnEntityHit(entity)
                      : ability.OnEntityMiss(entity);
        }
    }
    return remove;
}

bool Projectile::TestWorldCollisions(float3 origin, float3 target)
{
    return false; // TODO
}
