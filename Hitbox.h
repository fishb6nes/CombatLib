#pragma once

#include <algorithm>
#include <vector>

#include "./math.h"
#include "Entity.h"

namespace Combat
{
    class Hitbox
    {
    public:
        virtual std::vector<Entity *> GetEntityCollisions(float3 origin, float3 target,
                                                          EntityService &entityService) = 0;

        virtual std::vector<float3> GetWorldCollisions(float3 origin, float3 target) = 0;
    };

    class SphericalHitbox : public Hitbox
    {
    private:
        float radius;

    public:
        explicit SphericalHitbox(float radius)
                : radius { radius } { }

    public:
        std::vector<Entity *> GetEntityCollisions(float3 origin, float3 target,
                                                  EntityService &entityService) override
        {
            return { }; // TODO
        }

        std::vector<float3> GetWorldCollisions(float3 origin, float3 target) override
        {
            return { }; // TODO
        }
    };

    class TargetedSphericalHitbox : public SphericalHitbox
    {
    private:
        int entityId;

    public:
        TargetedSphericalHitbox(float radius, int entityId)
                : SphericalHitbox(radius), entityId { entityId } { }

    public:
        std::vector<Entity *> GetEntityCollisions(float3 origin, float3 target,
                                                  EntityService &entityService) override
        {
            auto entities = SphericalHitbox::GetEntityCollisions(origin, target, entityService);
            auto predicate = [this](Entity *entity) { return entity->GetCombatId() == entityId; };
            auto removed = std::remove_if(entities.begin(), entities.end(), predicate);
            entities.erase(removed, entities.end());
            return entities;
        }

        std::vector<float3> GetWorldCollisions(float3 origin, float3 target) override
        {
            return { }; // TODO
        }
    };

    class VoidHitbox : public Hitbox
    {
    public:
        std::vector<Entity *> GetEntityCollisions(float3 origin, float3 target,
                                                  EntityService &entityService) override { return { }; }

        std::vector<float3> GetWorldCollisions(float3 origin, float3 target) override { return { }; }
    };
}
