#pragma once

#include <map>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>

#include "Modifier.h"
#include "Status.h"

namespace Combat
{
    namespace Status
    {
        class Affectable;
    }

    namespace Ability
    {
        typedef int Attribute;
        typedef std::map<Attribute, float> Config;
        typedef std::map<Attribute, std::vector<Modifier>> Modifiers;

        class Base
        {
        public:
            virtual bool OnHit(Status::Affectable &entity) = 0;

            virtual bool OnMiss(Status::Affectable &entity) = 0;
        };

        template<class Entity, class Location>
        class Targeted : public Base
        {
        public:
            virtual ~Targeted() = default;

            virtual bool OnObstacle(Location location) { return false; };

        public:
            class Factory
            {
            public:
                virtual std::unique_ptr<Targeted> Create(
                        Entity &caster, Entity &target, const Config &config, Modifiers modifiers) = 0;

//                virtual std::unique_ptr<Targeted> Create(
//                        Entity &caster, Location &target, const Config &config, Modifiers modifiers) = 0;
            };
        };

        template<class Entity, class Location>
        class Targetless : public Base
        {
        public:
            virtual bool OnObstacle(Location location) { return true; };

            virtual bool OnMaxRange(Location location) { return true; };

        public:
            class Factory
            {
            public:
                virtual std::unique_ptr<Targetless> Create(
                        Entity &caster, const Config &config, Modifiers modifiers) = 0;
            };
        };

        template<class Entity, class ParentAbility, class ChildData>
        class Child : public Base
        {
        public:
            class Factory
            {
            public:
                virtual std::unique_ptr<Child> Create(
                        ParentAbility &parent, ChildData data, const Config &config, Modifiers modifiers) = 0;
            };
        };
    }
}
