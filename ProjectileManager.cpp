#include "ProjectileManager.h"

using namespace Combat;

void ProjectileManager::AddProjectile(Projectile *projectile)
{
    projectiles.insert({ projectile, projectile });
}

void ProjectileManager::RemoveProjectile(Projectile *projectile)
{
    projectiles.erase(projectile);
}

void ProjectileManager::UpdateProjectiles()
{
    for (auto it = projectiles.begin(); it != projectiles.end(); /* manual incr */)
    {
        if (it->second->Update(abilityService, entityService))
        {
            it = projectiles.erase(it);
        }
        else ++it;
    }
}
