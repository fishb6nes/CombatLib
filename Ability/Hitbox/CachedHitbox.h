#pragma once

#include <set>
#include <vector>

#include "../../Entity/Entity.h"
#include "../../Entity/EntityService.h"

#include "BasicHitbox.h"

namespace Combat
{
    class CachedHitbox : BasicHitbox
    {
        const EntityService &entityService;

        std::set<Entity *> cache;

    public:
        explicit CachedHitbox(const EntityService &entityService)
                : entityService { entityService } { }

        inline const std::set<Entity *> &
        ViewEntitiesHit() const { return cache; }

    public:
        std::vector<Entity *>
        FindEntityCollisions(float3 origin, float3 target)
        {
            auto entities = hitbox.TestEntityCollisions(origin, target);
            auto predicate = [this](Entity *entity) { return entitiesHit.find(entity) != entitiesHit.end(); };
            auto removed = std::remove_if(entities.begin(), entities.end(), predicate);
            entities.erase(removed, entities.end());
            entitiesHit.insert(entities.begin(), entities.end());
            return std::move(entities);
        }
    };
}
