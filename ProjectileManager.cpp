#include "ProjectileManager.h"

using namespace Combat;

void ProjectileManager::CreateProjectile(Ability &ability, Movement &movement, Hitbox &hitbox)
{
    auto projectile = std::make_unique<Projectile>(abilityService,
                                                   ability, movement, hitbox);
    projectiles.push_back(std::move(projectile));
}

void ProjectileManager::TickProjectiles()
{
    for (auto it = projectiles.begin(); it != projectiles.end(); /* manual */)
    {
        it = (*it)->Tick() ? projectiles.erase(it) : ++it;
    }
}
