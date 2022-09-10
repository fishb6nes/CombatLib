#pragma once

#include <memory>
#include <set>

namespace Combat
{
    class AbilityService;

    class Ability;
    class Movement;
    class Hitbox;

    struct float3;
}

namespace Combat
{
    class Projectile
    {
    private:
        AbilityService &abilityService;

        Ability &ability;
        Movement &movement;
        Hitbox &hitbox;

    public:
        Projectile(AbilityService &abilityService,
                   Ability &ability, Movement &movement, Hitbox &hitbox)
                : abilityService { abilityService },
                  ability { ability }, movement { movement }, hitbox { hitbox } { }

    public:
        bool Tick();

    private:
        bool CollideEntities(float3 origin, float3 target);

        bool CollideWorld(float3 origin, float3 target);
    };
}
