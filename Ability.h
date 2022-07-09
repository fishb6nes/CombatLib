#pragma once

#include <map>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>

#include "Modifier.h"

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

        class Snapshot
        {
            friend class Service;

        private:
            std::string_view name;
            const Config &config;
            Status::Affectable &caster;
            Status::Affectable *target;
            Modifiers modifiers;

        public:
            Snapshot(
                    std::string_view name, const Config &config, Status::Affectable &caster,
                    Status::Affectable *target, Modifiers modifiers = { })
                    : name { name }, config { config }, caster { caster }, target { target },
                      modifiers { std::move(modifiers) } { }

            inline std::string_view GetName() const { return name; }

            inline const Config &GetConfig() const { return config; }

            inline Status::Affectable &GetCaster() const { return caster; }

            inline Status::Affectable *GetTarget() const { return target; }

            inline const Modifiers &GetModifiers() const { return modifiers; }
        };

        template<class Entity>
        class Base
        {
            virtual bool OnHit(Entity entity) = 0;

            virtual bool OnMiss(Entity entity) = 0;
        };

        template<class Entity, class Location>
        class Targeted : public Base<Entity>
        {
        public:
            virtual bool OnObstacle(Location location) { return false; };

        public:
            class Factory
            {
            public:
                virtual std::unique_ptr<Targeted> Create(
                        const Entity &caster, Snapshot snapshot, Entity target) = 0;

                virtual std::unique_ptr<Targeted> Create(
                        const Entity &caster, Snapshot snapshot, Location target) = 0;
            };
        };

        template<class Entity, class Location>
        class Targetless : public Base<Entity>
        {
        public:
            virtual bool OnGrounded(Location location) { return true; };

            virtual bool OnMaxRange(Location location) { return true; };

        public:
            class Factory
            {
            public:
                virtual std::unique_ptr<Targetless> Create(const Entity &caster, Snapshot snapshot) = 0;
            };
        };

        class Child
        {
        public:
            template<class Entity, class ParentAbility, class ChildData>
            class Factory
            {
            public:
                virtual std::unique_ptr<Child> Create(
                        const ParentAbility &parent, Snapshot snapshot, ChildData data) = 0;
            };
        };
    }
}
