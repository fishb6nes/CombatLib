#pragma once

#include <map>
#include <set>
#include <vector>

#include "Ability.h"
#include "AbilityService.h"
#include "Hitbox.h"
#include "Movement.h"

namespace Combat
{
    struct Projectile
    {
        int id;
        Ability::Base &ability;
        Movement &movement;
        Hitbox &hitbox;
        std::set<int> entitiesHit;
    };

    class ProjectileManager
    {
    private:
        inline static int idSequence = 0;

    private:
        Ability::Service &abilityService;
        EntityService &entityService;
        std::map<int, Projectile> projectiles;

    public:
        explicit ProjectileManager(Ability::Service &abilityService, EntityService &entityService)
                : abilityService { abilityService }, entityService { entityService } { }

        void CreateProjectile(Ability::Base &ability, Movement &movement, Hitbox &hitbox)
        {
            Projectile projectile { idSequence++, ability, movement, hitbox, { }};
            projectiles.insert({ projectile.id, std::move(projectile) });
        }

        void RemoveProjectile(int id)
        {
            projectiles.erase(id);
        }

        void UpdateProjectiles()
        {
            std::vector<int> removedProjectiles;

            for (auto &[id, projectile] : projectiles)
            {
                if (UpdateProjectile(projectile))
                {
                    removedProjectiles.push_back(id);
                }
            }

            for (int id : removedProjectiles)
            {
                RemoveProjectile(id);
            }
        }

    private:
        bool UpdateProjectile(Projectile &projectile)
        {
            auto &[id, ability, movement, hitbox, entitiesHit] = projectile;
            if (movement.HasNext())
            {
                auto origin = movement.Get();
                auto target = movement.Next();

                // Entity collision
                auto entities = projectile.hitbox.GetEntityCollisions(entityService);
                for (auto &entity : entities)
                {
                    if (entitiesHit.find(entity.id) != entitiesHit.end())
                    {
                        // save entity regardless of whether hit event succeeds as otherwise
                        // it'd come right back next tick and not count as a proper miss
                        entitiesHit.insert(entity.id);
                        return abilityService.PublishHitEvents(ability.name, ability.caster, entity)
                               ? ability.OnHit(entity)
                               : ability.OnMiss(entity);
                    }
                }

                // World collision
                // TODO
            }
            else if (ability.OnMaxRange(movement.Get()))
            {
                return true;
            }
            else return false;
        }
    };
}
