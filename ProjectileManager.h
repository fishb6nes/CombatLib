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

        std::vector<std::unique_ptr<Projectile>> projectiles;

    public:
        explicit ProjectileManager(AbilityService &abilityService)
                : abilityService { abilityService } { }

    public:
        void CreateProjectile(Ability &ability, Movement &movement, Hitbox &hitbox);

    private:
        void TickProjectiles();
    };
}
