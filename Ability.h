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

    class Ability
    {
    public:
        typedef int Attribute;
        typedef std::map<Attribute, float> Config;
        typedef std::map<Attribute, std::vector<Modifier>> Modifiers;

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
                    Entity &caster, Entity &target, const Ability::Config &config,
                    Ability::Modifiers modifiers) = 0;

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
                    Entity &caster, const Ability::Config &config, Ability::Modifiers modifiers) = 0;
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
                    ParentAbility &parent, ChildData data, const Ability::Config &config,
                    Ability::Modifiers modifiers) = 0;
        };
    };
}
