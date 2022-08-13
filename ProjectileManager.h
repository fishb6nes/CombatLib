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
        inline static int idSequence = 0;

    private:
        AbilityService &abilityService;
        EntityService &entityService;
        std::map<int, Projectile> projectiles;

    public:
        ProjectileManager(AbilityService &abilityService, EntityService &entityService)
                : abilityService { abilityService }, entityService { entityService } { }

    public:
        Projectile &CreateProjectile(Ability &ability, Movement &movement, Hitbox &hitbox);

        void RemoveProjectile(Projectile &projectile);

        void UpdateProjectiles();
    };
}
