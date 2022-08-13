#pragma once

#include <map>

#include "Projectile.h"

namespace Combat
{
    class Ability;
    class AbilityService;
    class EntityService;
    class Hitbox;
    class Movement;

    class ProjectileManager
    {
    private:
        AbilityService &abilityService;
        EntityService &entityService;
        std::map<Projectile *, Projectile *> projectiles;

    public:
        ProjectileManager(AbilityService &abilityService, EntityService &entityService)
                : abilityService { abilityService }, entityService { entityService } { }

    public:
        void AddProjectile(Projectile *projectile);

        void RemoveProjectile(Projectile *projectile);

        void UpdateProjectiles();
    };
}
