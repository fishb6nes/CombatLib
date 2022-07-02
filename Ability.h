#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Modifier.h"

namespace Combat::Ability
{
    class Configuration
    {

    };

    template<class Entity>
    class Snapshot
    {
    public:
        const std::map<int, std::vector<Modifier<Entity>>> modifiers;
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
                    const Entity &caster, Snapshot<Entity> snapshot, Entity target) = 0;

            virtual std::unique_ptr<Targeted> Create(
                    const Entity &caster, Snapshot<Entity> snapshot, Location target) = 0;
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
            virtual std::unique_ptr<Targetless> Create(const Entity &caster, Snapshot<Entity> snapshot) = 0;
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
                    const ParentAbility &parent, Snapshot<Entity> snapshot, ChildData data) = 0;
        };
    };
}
