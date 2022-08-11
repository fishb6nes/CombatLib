#pragma once

#include <map>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>

#include "Entity.h"
#include "Modifier.h"

namespace Combat
{
    class Entity;

    typedef int AbilityAttribute;
    typedef std::map<AbilityAttribute, float> AbilityConfig;
    typedef std::map<AbilityAttribute, std::vector<Modifier>> AbilityModifiers;

    class Ability
    {
    public:
        virtual bool OnHit(Entity &entity) = 0;

        virtual bool OnMiss(Entity &entity) = 0;
    };

    template<class Entity, class Location>
    class Targeted : public Ability
    {
    public:
        virtual ~Targeted() = default;

        virtual bool OnObstacle(Location location) { return false; };

    public:
        class Factory
        {
        public:
            virtual std::unique_ptr<Targeted> Create(
                    Entity &caster, Entity &target, const AbilityConfig &config,
                    AbilityModifiers modifiers) = 0;

//                virtual std::unique_ptr<Targeted> Create(
//                        Entity &caster, Location &target, const AbilityConfig &config, AbilityModifiers modifiers) = 0;
        };
    };

    template<class Entity, class Location>
    class Targetless : public Ability
    {
    public:
        virtual bool OnObstacle(Location location) { return true; };

        virtual bool OnMaxRange(Location location) { return true; };

    public:
        class Factory
        {
        public:
            virtual std::unique_ptr<Targetless> Create(
                    Entity &caster, const AbilityConfig &config, AbilityModifiers modifiers) = 0;
        };
    };

    template<class Entity, class ParentAbility, class ChildData>
    class Child : public Ability
    {
    public:
        class Factory
        {
        public:
            virtual std::unique_ptr<Child> Create(
                    ParentAbility &parent, ChildData data, const AbilityConfig &config,
                    AbilityModifiers modifiers) = 0;
        };
    };
}
