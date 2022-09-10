#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#include "./math.h"
#include "Entity.h"
#include "EntityService.h"

namespace Combat
{
    /**
     * An interface representing a type of collision detection in 3D space.
     */
    class Hitbox
    {
    public:
        virtual std::vector<Entity *> TestEntityCollisions(float3 origin, float3 target) = 0;

        virtual std::vector<float3> TestWorldCollisions(float3 origin, float3 target) = 0;
    };

    /**
     * A simple hitbox that tests for collisions within its `radius`.
     */
    class SphericalHitbox : public Hitbox
    {
    private:
        EntityService &entityService;

        float radius;

    public:
        SphericalHitbox(EntityService &entityService,
                        float radius)
                : entityService { entityService },
                  radius { radius } { }

    public:
        std::vector<Entity *> TestEntityCollisions(float3 origin, float3 target) override
        {
            return { }; // TODO
        }

        std::vector<float3> TestWorldCollisions(float3 origin, float3 target) override
        {
            return { }; // TODO
        }
    };

    /**
     * A no-op hitbox that will never collide with anything.
     */
    class VoidHitbox : public Hitbox
    {
    public:
        std::vector<Entity *> TestEntityCollisions(float3 origin, float3 target) override
        {
            return { };
        }

        std::vector<float3> TestWorldCollisions(float3 origin, float3 target) override
        {
            return { };
        }
    };

    /**
     * A hitbox decorator preventing entities from being collided with multiple times over multiple ticks.
     */
    class CachedHitbox : public Hitbox
    {
    private:
        Hitbox &hitbox;
        std::set<Entity *> entitiesHit;

    public:
        explicit CachedHitbox(Hitbox &hitbox)
                : hitbox { hitbox } { }

    public:
        inline const std::set<Entity *> &GetEntitiesHit() const { return entitiesHit; }

    public:
        std::vector<Entity *> TestEntityCollisions(float3 origin, float3 target) override
        {
            auto entities = hitbox.TestEntityCollisions(origin, target);
            auto predicate = [this](Entity *entity) { return entitiesHit.find(entity) != entitiesHit.end(); };
            auto removed = std::remove_if(entities.begin(), entities.end(), predicate);
            entities.erase(removed, entities.end());
            entitiesHit.insert(entities.begin(), entities.end());
            return std::move(entities);
        }
    };

    /**
     * A hitbox decorator filtering out any entities it is not specifically targeting.
     */
    class TargetedHitbox : public Hitbox
    {
    private:
        Hitbox &hitbox;
        int entityId;

    public:
        TargetedHitbox(Hitbox &hitbox, int entityId)
                : hitbox { hitbox }, entityId { entityId } { }

    public:
        std::vector<Entity *> TestEntityCollisions(float3 origin, float3 target) override
        {
            auto entities = hitbox.TestEntityCollisions(origin, target);
            auto predicate = [this](Entity *entity) { return entity->GetCombatId() != entityId; };
            auto removed = std::remove_if(entities.begin(), entities.end(), predicate);
            entities.erase(removed, entities.end());
            return std::move(entities);
        }

        std::vector<float3> TestWorldCollisions(float3 origin, float3 target) override
        {
            return hitbox.TestWorldCollisions(origin, target);
        }
    };
}
