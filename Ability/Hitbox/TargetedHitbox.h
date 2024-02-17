#pragma once

#include "BasicHitbox.h"

namespace Combat
{
    class TargetedHitbox : BasicHitbox
    {
    public:
    };
}

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