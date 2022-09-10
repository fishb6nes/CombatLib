#pragma once

#include <memory>
#include <set>

namespace Combat
{
    class Projectile
    {
    private:
        class AbilityService &abilityService;

        class Ability &ability;
        class Movement &movement;
        class Hitbox &hitbox;

    public:
        Projectile(AbilityService &abilityService,
                   Ability &ability, Movement &movement, Hitbox &hitbox)
                : abilityService { abilityService },
                  ability { ability }, movement { movement }, hitbox { hitbox } { }

    public:
        bool Tick();

    private:
        bool CollideEntities(struct float3 origin, struct float3 target);

        bool CollideWorld(struct float3 origin, struct float3 target);
    };
}
