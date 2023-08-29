#pragma once

#include "Hitbox/AABBHitbox.h"
#include "Hitbox/SphereHitbox.h"

namespace Combat
{
    struct Hitbox
    {
        enum Type
        {
            AABB,
            SPHERE,
        } type;

        union
        {
            AABBHitbox _aabb;
            SphereHitbox _sphere;
        };

        Hitbox(const AABBHitbox &it)
                : type { AABB }, _aabb { it } { }

        Hitbox(const SphereHitbox &it)
                : type { SPHERE }, _sphere { it } { }

        operator AABBHitbox() const { return _aabb; }
        operator SphereHitbox() const { return _sphere; }

        static Hitbox
        Translate(const Hitbox &it, float3 location)
        {
            switch (it.type)
            {
                case AABB: return AABBHitbox::Translate(it, location);
                case SPHERE: return SphereHitbox::Translate(it, location);
            }
        }

        static bool
        TestAABB(const Hitbox &it, const AABBHitbox &other)
        {
            switch (it.type)
            {
                case AABB: return AABBHitbox::TestAABB(it, other);
                case SPHERE: return SphereHitbox::TestAABB(it, other);
            }
        }

        static bool
        TestSphere(const Hitbox &it, const SphereHitbox &other)
        {
            switch (it.type)
            {
                case AABB: return AABBHitbox::TestSphere(it, other);
                case SPHERE: return SphereHitbox::TestSphere(it, other);
            }
        }

        static bool
        Test(const Hitbox &it, const Hitbox &other)
        {
            switch (other.type)
            {
                case AABB: return TestAABB(it, other);
                case SPHERE: return TestSphere(it, other);
            }
        }
    };

    // TODO remove
//    /**
//     * A hitbox decorator preventing entities from being collided with multiple times over multiple ticks.
//     */
//    class CachedHitbox : public Hitbox
//    {
//    private:
//        Hitbox &hitbox;
//        std::set<Entity *> entitiesHit;
//
//    public:
//        explicit CachedHitbox(Hitbox &hitbox)
//                : hitbox { hitbox } { }
//
//    public:
//        inline const std::set<Entity *> &GetEntitiesHit() const { return entitiesHit; }
//
//    public:
//        std::vector<Entity *> TestEntityCollisions(float3 origin, float3 target) override
//        {
//            auto entities = hitbox.TestEntityCollisions(origin, target);
//            auto predicate = [this](Entity *entity) { return entitiesHit.find(entity) != entitiesHit.end(); };
//            auto removed = std::remove_if(entities.begin(), entities.end(), predicate);
//            entities.erase(removed, entities.end());
//            entitiesHit.insert(entities.begin(), entities.end());
//            return std::move(entities);
//        }
//    };
//
//    /**
//     * A hitbox decorator filtering out any entities it is not specifically targeting.
//     */
//    class TargetedHitbox : public Hitbox
//    {
//    private:
//        Hitbox &hitbox;
//        int entityId;
//
//    public:
//        TargetedHitbox(Hitbox &hitbox, int entityId)
//                : hitbox { hitbox }, entityId { entityId } { }
//
//    public:
//        std::vector<Entity *> TestEntityCollisions(float3 origin, float3 target) override
//        {
//            auto entities = hitbox.TestEntityCollisions(origin, target);
//            auto predicate = [this](Entity *entity) { return entity->GetCombatId() != entityId; };
//            auto removed = std::remove_if(entities.begin(), entities.end(), predicate);
//            entities.erase(removed, entities.end());
//            return std::move(entities);
//        }
//
//        std::vector<float3> TestWorldCollisions(float3 origin, float3 target) override
//        {
//            return hitbox.TestWorldCollisions(origin, target);
//        }
//    };
}
