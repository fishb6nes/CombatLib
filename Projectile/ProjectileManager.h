#pragma once

#include <memory>
#include <vector>

#include "Projectile.h"

namespace Combat
{
    class ProjectileManager
    {
    private:
        class AbilityService &abilityService;
        class EntityService &entityService;

        std::vector<Projectile> projectiles;

    public:
        explicit ProjectileManager(AbilityService &abilityService, EntityService &entityService)
                : abilityService { abilityService }, entityService { entityService } { }

    public:
        void
        CreateProjectile(Ability *ability, const Hitbox &hitbox, const Movement &movement);

    private:
        void
        TickProjectiles();
    };
}
