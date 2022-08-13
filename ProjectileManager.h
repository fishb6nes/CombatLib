#pragma once

#include <map>

#include "Projectile.h"

namespace Combat
{
    class AbilityService;
    class EntityService;
}

namespace Combat
{
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
