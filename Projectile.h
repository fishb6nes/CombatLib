#pragma once

#include <set>

namespace Combat
{
    class Ability;
    class AbilityService;
    class EntityService;
    class float3;
    class Hitbox;
    class Movement;
}

namespace Combat
{
    class Projectile
    {
    private:
        inline static int idSequence = 0;

    private:
        int id;
        Ability &ability;
        Movement &movement;
        Hitbox &hitbox;
        std::set<int> entitiesHit;

    public:
        Projectile(Ability &ability, Movement &movement, Hitbox &hitbox)
                : id { idSequence++ }, ability { ability }, movement { movement }, hitbox { hitbox } { }

        inline int GetId() const { return id; }

        inline Ability &GetAbility() const { return ability; }

        inline Movement &GetMovement() const { return movement; }

        inline Hitbox &GetHitbox() const { return hitbox; }

        inline const std::set<int> &GetEntitiesHit() const { return entitiesHit; }

    public:
        bool Update(AbilityService &abilityService, EntityService &entityService);

    private:
        bool TestEntityCollisions(float3 origin, float3 target,
                                  AbilityService &abilityService, EntityService &entityService);

        bool TestWorldCollisions(float3 origin, float3 target);
    };
}
