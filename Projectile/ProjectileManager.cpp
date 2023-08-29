#include "../math.h"
#include "../Ability/Ability.h"
#include "../Ability/AbilityService.h"
#include "../Entity/EntityService.h"

#include "ProjectileManager.h"

using namespace Combat;

void
ProjectileManager::CreateProjectile(Ability *ability, const Hitbox &hitbox, const Movement &movement)
{
    projectiles.push_back({ ability, hitbox, movement });
}

void
ProjectileManager::TickProjectiles()
{
    for (auto it = projectiles.begin() ; it != projectiles.end() ; /* manual incr */)
    {
        auto &[ability, hitbox, movement] = *it;

        float3 origin = movement.location;
        if (Movement::HasNext(movement))
        {
            Movement target = Movement::SetNext(movement);

            auto entities = entityService.GetNearbyEntities(target.location);
            for (auto &entity : entities)
            {
                auto abilityHitbox = Hitbox::Translate(hitbox, target.location);
                auto entityHitbox = Hitbox::Translate(entity.GetHitbox(), target.location);
                auto collision = Hitbox::Test(abilityHitbox, entityHitbox);

                bool remove = collision && abilityService.PublishHitEvents(*ability, entity)
                              ? ability->OnEntityHit(entity)
                              : ability->OnEntityMiss(entity);

                if (remove) projectiles.erase(it);
            }

            movement = target;
            ++it;
        }
        else
        {
            it->ability->OnProjectileOutOfRange(0);
            projectiles.erase(it);
        }
    }
}
