#include "ProjectileManager.h"

using namespace Combat;

Projectile &ProjectileManager::CreateProjectile(Ability &ability, Movement &movement, Hitbox &hitbox)
{
    int id = idSequence++;
    Projectile projectile { id, ability, movement, hitbox };
    return projectiles.insert({ id, std::move(projectile) }).first->second;
}

void ProjectileManager::RemoveProjectile(Projectile &projectile)
{
    projectiles.erase(projectile.GetId());
}

void ProjectileManager::UpdateProjectiles()
{
    for (auto it = projectiles.begin(); it != projectiles.end(); /* manual incr */)
    {
        if (it->second.Update(abilityService, entityService))
        {
            it = projectiles.erase(it);
        }
        else ++it;
    }
}
