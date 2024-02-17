#pragma once

#include <map>
#include <unordered_map>
#include <memory>
#include <ranges>
#include <set>
#include <typeindex>
#include <vector>

#include "../math.h"

#include "../Ability/Ability.h"

#include "Movement.h"

#ifndef COMBAT_PROJECTILE_MAX_RANGE
#define COMBAT_PROJECTILE_MAX_RANGE 100
#endif

namespace Combat
{
    struct Hitbox
    {
        enum class Shape
        {
            SPHERE,
        };

        enum class Type
        {
            SIMPLE,
            CACHED,
            TARGETED
        };
    };

    struct Movement2
    {
        enum Type
        {
            ENTITY,
            LINEAR,
            ONESHOT,
            STATIC
        };
    };

    // NOTE no union, no point making a fast system if 40b of data is irrelevant in the cache

    template<typename Movement, typename Hitbox>
    class ProjectileRegistry
    {
        std::vector<Ability *> abilities;
        std::vector<Movement> movements;
        std::vector<Hitbox> hitboxes;

    public:
        inline std::vector<Movement> &
        GetMovements() { return movements; }

        inline std::vector<Hitbox> &
        GetHitboxes() { return hitboxes; }

    public:
        void
        RegisterProjectile(Ability *ability, Movement movement, Hitbox hitbox)
        {
            abilities.push_back(ability);
            movements.push_back(movement);
            hitboxes.push_back(hitbox);
        }
    };

    class ProjectileSystem
    {
        struct SimpleSphereHitboxData
        {
            sphere shape;
        };

        struct CachedSphereHitboxData
        {
            sphere shape;
            std::set<uint_fast64_t> cache;
        };

        struct TargetedSphereHitboxData
        {
            sphere shape;
            uint_fast64_t target;
        };

        typedef std::tuple<std::type_index, std::type_index> RegistryKey;

        std::set<std::type_index>

        std::map<RegistryKey, std::unique_ptr<void>> registries;

        ProjectileSystem()
        {
            AddRegistry<StaticMovement, SimpleSphereHitboxData>();
            AddRegistry<StaticMovement, CachedSphereHitboxData>();
            AddRegistry<StaticMovement, TargetedSphereHitboxData>();

            AddRegistry<OneShotMovement, SimpleSphereHitboxData>();
            AddRegistry<OneShotMovement, CachedSphereHitboxData>();
            AddRegistry<OneShotMovement, TargetedSphereHitboxData>();

            AddRegistry<LinearMovement, SimpleSphereHitboxData>();
            AddRegistry<LinearMovement, CachedSphereHitboxData>();
            AddRegistry<LinearMovement, TargetedSphereHitboxData>();

            AddRegistry<EntityMovement, SimpleSphereHitboxData>();
            AddRegistry<EntityMovement, CachedSphereHitboxData>();
            AddRegistry<EntityMovement, TargetedSphereHitboxData>();
        }

        template<Movement Movement>
        void
        AddMovement()
        {

        }


        template<typename Movement, typename Hitbox>
        void
        AddRegistry()
        {
            registries[{ typeid(Movement), typeid(Hitbox) }] =
                    std::make_unique<ProjectileRegistry<Movement, Hitbox>>();
        }
















        std::vector<Ability *> abilities_StaticMovement_SimpleSphereHitbox;
        std::vector<StaticMovement> movements_StaticMovement_SimpleSphereHitbox;
        std::vector<SimpleSphereHitboxData> hitboxes_StaticMovement_SimpleSphereHitbox;

        std::vector<Ability *> abilities_OneShotMovement_SimpleSphereHitbox;
        std::vector<OneShotMovement> movements_OneShotMovement_SimpleSphereHitbox;
        std::vector<SimpleSphereHitboxData> hitboxes_OneShotMovement_SimpleSphereHitbox;

        std::vector<Ability *> abilities_LinearMovement_SimpleSphereHitbox;
        std::vector<LinearMovement> movements_LinearMovement_SimpleSphereHitbox;
        std::vector<SimpleSphereHitboxData> hitboxes_LinearMovement_SimpleSphereHitbox;

        std::vector<Ability *> abilities_EntityMovement_SimpleSphereHitbox;
        std::vector<EntityMovement> movements_EntityMovement_SimpleSphereHitbox;
        std::vector<SimpleSphereHitboxData> hitboxes_EntityMovement_SimpleSphereHitbox;

        std::vector<Ability *> abilities_StaticMovement_CachedSphereHitbox;
        std::vector<StaticMovement> movements_StaticMovement_CachedSphereHitbox;
        std::vector<CachedSphereHitboxData> hitboxes_StaticMovement_CachedSphereHitbox;

        std::vector<Ability *> abilities_OneShotMovement_CachedSphereHitbox;
        std::vector<OneShotMovement> movements_OneShotMovement_CachedSphereHitbox;
        std::vector<CachedSphereHitboxData> hitboxes_OneShotMovement_CachedSphereHitbox;

        std::vector<Ability *> abilities_LinearMovement_CachedSphereHitbox;
        std::vector<LinearMovement> movements_LinearMovement_CachedSphereHitbox;
        std::vector<CachedSphereHitboxData> hitboxes_LinearMovement_CachedSphereHitbox;

        std::vector<Ability *> abilities_EntityMovement_CachedSphereHitbox;
        std::vector<EntityMovement> movements_EntityMovement_CachedSphereHitbox;
        std::vector<CachedSphereHitboxData> hitboxes_EntityMovement_CachedSphereHitbox;

        std::vector<Ability *> abilities_StaticMovement_TargetedSphereHitbox;
        std::vector<StaticMovement> movements_StaticMovement_TargetedSphereHitbox;
        std::vector<TargetedSphereHitboxData> hitboxes_StaticMovement_TargetedSphereHitbox;

        std::vector<Ability *> abilities_OneShotMovement_TargetedSphereHitbox;
        std::vector<OneShotMovement> movements_OneShotMovement_TargetedSphereHitbox;
        std::vector<TargetedSphereHitboxData> hitboxes_OneShotMovement_TargetedSphereHitbox;

        std::vector<Ability *> abilities_LinearMovement_TargetedSphereHitbox;
        std::vector<LinearMovement> movements_LinearMovement_TargetedSphereHitbox;
        std::vector<TargetedSphereHitboxData> hitboxes_LinearMovement_TargetedSphereHitbox;

        std::vector<Ability *> abilities_EntityMovement_TargetedSphereHitbox;
        std::vector<EntityMovement> movements_EntityMovement_TargetedSphereHitbox;
        std::vector<TargetedSphereHitboxData> hitboxes_EntityMovement_TargetedSphereHitbox;

        ProjectileSystem(int reserve = 256)
        {
            abilities_StaticMovement_SimpleSphereHitbox.reserve(reserve);
            movements_StaticMovement_SimpleSphereHitbox.reserve(reserve);
            hitboxes_StaticMovement_SimpleSphereHitbox.reserve(reserve);

            abilities_OneShotMovement_SimpleSphereHitbox.reserve(reserve);
            movements_OneShotMovement_SimpleSphereHitbox.reserve(reserve);
            hitboxes_OneShotMovement_SimpleSphereHitbox.reserve(reserve);

            abilities_LinearMovement_SimpleSphereHitbox.reserve(reserve);
            movements_LinearMovement_SimpleSphereHitbox.reserve(reserve);
            hitboxes_LinearMovement_SimpleSphereHitbox.reserve(reserve);

            abilities_EntityMovement_SimpleSphereHitbox.reserve(reserve);
            movements_EntityMovement_SimpleSphereHitbox.reserve(reserve);
            hitboxes_EntityMovement_SimpleSphereHitbox.reserve(reserve);

            abilities_StaticMovement_CachedSphereHitbox.reserve(reserve);
            movements_StaticMovement_CachedSphereHitbox.reserve(reserve);
            hitboxes_StaticMovement_CachedSphereHitbox.reserve(reserve);

            abilities_OneShotMovement_CachedSphereHitbox.reserve(reserve);
            movements_OneShotMovement_CachedSphereHitbox.reserve(reserve);
            hitboxes_OneShotMovement_CachedSphereHitbox.reserve(reserve);

            abilities_LinearMovement_CachedSphereHitbox.reserve(reserve);
            movements_LinearMovement_CachedSphereHitbox.reserve(reserve);
            hitboxes_LinearMovement_CachedSphereHitbox.reserve(reserve);

            abilities_EntityMovement_CachedSphereHitbox.reserve(reserve);
            movements_EntityMovement_CachedSphereHitbox.reserve(reserve);
            hitboxes_EntityMovement_CachedSphereHitbox.reserve(reserve);

            abilities_StaticMovement_TargetedSphereHitbox.reserve(reserve);
            movements_StaticMovement_TargetedSphereHitbox.reserve(reserve);
            hitboxes_StaticMovement_TargetedSphereHitbox.reserve(reserve);

            abilities_OneShotMovement_TargetedSphereHitbox.reserve(reserve);
            movements_OneShotMovement_TargetedSphereHitbox.reserve(reserve);
            hitboxes_OneShotMovement_TargetedSphereHitbox.reserve(reserve);

            abilities_LinearMovement_TargetedSphereHitbox.reserve(reserve);
            movements_LinearMovement_TargetedSphereHitbox.reserve(reserve);
            hitboxes_LinearMovement_TargetedSphereHitbox.reserve(reserve);

            abilities_EntityMovement_TargetedSphereHitbox.reserve(reserve);
            movements_EntityMovement_TargetedSphereHitbox.reserve(reserve);
            hitboxes_EntityMovement_TargetedSphereHitbox.reserve(reserve);
        }

        void
        CreateProjectile(Ability *ability, StaticMovement movement, sphere hitbox)
        {
            abilities_StaticMovement_SimpleSphereHitbox.push_back(ability);
            movements_StaticMovement_SimpleSphereHitbox.push_back(movement);
            hitboxes_StaticMovement_SimpleSphereHitbox.push_back({ hitbox });
        }

        void
        TickMovements()
        {
            for (auto &movement : movements_OneShotMovement_SimpleSphereHitbox) movement.SetNext();
            for (auto &movement : movements_OneShotMovement_CachedSphereHitbox) movement.SetNext();
            for (auto &movement : movements_OneShotMovement_TargetedSphereHitbox) movement.SetNext();

            for (auto &movement : movements_LinearMovement_SimpleSphereHitbox) movement.SetNext();
            for (auto &movement : movements_LinearMovement_CachedSphereHitbox) movement.SetNext();
            for (auto &movement : movements_LinearMovement_TargetedSphereHitbox) movement.SetNext();

            for (auto &movement : movements_EntityMovement_SimpleSphereHitbox) movement.SetNext();
            for (auto &movement : movements_EntityMovement_CachedSphereHitbox) movement.SetNext();
            for (auto &movement : movements_EntityMovement_TargetedSphereHitbox) movement.SetNext();
        }

        void
        TickHitboxes()
        {
            for (int i = 0; i < hitboxes_StaticMovement_SimpleSphereHitbox.size(); ++i)
            {
                auto &movement = movements_StaticMovement_SimpleSphereHitbox[i];
                auto &hitbox = hitboxes_StaticMovement_SimpleSphereHitbox[i];
                hitbox = hitbox.shape + movement.location;
            }

            for (auto &it : hitboxes_StaticMovement_SimpleSphereHitbox.iter)
            {
                auto &movement = movements_StaticMovement_SimpleSphereHitbox[];
                hitbox = hitbox.shape + movement.location;
            }
            for (auto &hitbox : hitboxes_StaticMovement_CachedSphereHitbox) movement.SetNext();
            for (auto &hitbox : hitboxes_StaticMovement_TargetedSphereHitbox) movement.SetNext();

            for (auto &hitbox : hitboxes_OneShotMovement_SimpleSphereHitbox) movement.SetNext();
            for (auto &hitbox : hitboxes_OneShotMovement_CachedSphereHitbox) movement.SetNext();
            for (auto &hitbox : hitboxes_OneShotMovement_TargetedSphereHitbox) movement.SetNext();

            for (auto &hitbox : hitboxes_LinearMovement_SimpleSphereHitbox) movement.SetNext();
            for (auto &hitbox : hitboxes_LinearMovement_CachedSphereHitbox) movement.SetNext();
            for (auto &hitbox : hitboxes_LinearMovement_TargetedSphereHitbox) movement.SetNext();

            for (auto &hitbox : hitboxes_EntityMovement_SimpleSphereHitbox) movement.SetNext();
            for (auto &hitbox : hitboxes_EntityMovement_CachedSphereHitbox) movement.SetNext();
            for (auto &hitbox : hitboxes_EntityMovement_TargetedSphereHitbox) movement.SetNext();
        }
    };
}
