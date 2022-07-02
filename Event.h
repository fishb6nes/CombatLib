#pragma once

#include <map>
#include <string>
#include <vector>

#include "Modifier.h"

namespace Combat::Event
{
    template<class Entity, class Config>
    struct PreBase
    {
        bool isCancelled = false;
        bool isExplicitlyAllowed = false;
        std::map<Config, std::vector<Modifier<Entity>>> modifiers { };

        bool IsAllowed();

        void AddModifier(Config config, Modifier<Entity> modifier);
    };

    template<class Entity, class Config>
    struct AbilityPreCast : public PreBase<Entity, Config>
    {
        const std::string &ability;
        const Entity &caster;
    };

    template<class Entity>
    struct AbilityCast
    {
        const std::string &ability;
        const Entity &caster;
    };

    template<class Entity, class Config>
    struct AbilityPreHit : PreBase<Entity, Config>
    {
        const std::string &ability;
        const Entity &caster;
        const Entity &target;
    };

    template<class Entity>
    struct AbilityHit
    {
        const std::string &ability;
        const Entity &caster;
        const Entity &target;
    };

    template<class Entity>
    struct AbilityMiss
    {
        const std::string &ability;
        const Entity &caster;
        const Entity &target;
    };

    template<class Entity, class Config>
    class Handler
    {
    public:
        virtual void ApplyEvent(AbilityPreCast<Entity, Config> &event) { }

        virtual void ApplyEvent(const AbilityCast<Entity> &event) { }

        virtual void ApplyEvent(AbilityPreHit<Entity, Config> &event) { }

        virtual void ApplyEvent(const AbilityHit<Entity> &event) { }

        virtual void ApplyEvent(const AbilityMiss<Entity> &event) { }
    };

    template<class Entity, class Config>
    class Bus
    {
    private:
        std::vector<const Handler<Entity, Config> *> handlers { };

    public:
        void AddHandler(const Handler<Entity, Config> &handler);

        void RemoveHandler(const Handler<Entity, Config> &handler);

        template<class T>
        T PublishEvent(T &event) const;
    };
}
