#include "Projectile.h"

#include "Ability.h"
#include "AbilityService.h"
#include "Hitbox.h"
#include "Movement.h"

using namespace Combat;

bool Projectile::Tick()
{
    float3 origin = movement.Get();
    if (movement.HasNext())
    {
        float3 target = movement.Next();
        return CollideEntities(origin, target) || CollideWorld(origin, target);
    }
    else
    {
        ability.OnProjectileOutOfRange(*this);
        return true;
    }
}

bool Projectile::CollideEntities(float3 origin, float3 target)
{
    bool remove = false;
    auto collisions = hitbox.TestEntityCollisions(origin, target);
    for (Entity *collision : collisions)
    {
        Entity &entity = *collision;
        remove |= abilityService.PublishHitEvents(ability, entity)
                  ? ability.OnEntityHit(entity)
                  : ability.OnEntityMiss(entity);
    }
    return remove;
}

bool Projectile::CollideWorld(float3 origin, float3 target)
{
    return false; // TODO
}
