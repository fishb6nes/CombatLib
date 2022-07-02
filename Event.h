#pragma once

#include <map>
#include <string>
#include <vector>

#include "Modifier.h"

namespace Combat::Event
{
    template<class AbilityAttribute, class Entity>
    struct PreBase
    {
        bool isCancelled = false;
        bool isExplicitlyAllowed = false;
        std::map<AbilityAttribute, std::vector<Modifier<Entity>>> modifiers { };

        inline bool IsAllowed() const { return isExplicitlyAllowed || !isCancelled; }

        void AddModifier(AbilityAttribute attribute, Modifier<Entity> modifier);
    };

    template<class AbilityAttribute, class Entity>
    struct AbilityPreCast : public PreBase<AbilityAttribute, Entity>
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

    template<class AbilityAttribute, class Entity>
    struct AbilityPreHit : PreBase<AbilityAttribute, Entity>
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

    template<class AbilityAttribute, class Entity>
    class Handler
    {
    public:
        virtual void ApplyEvent(AbilityPreCast<AbilityAttribute, Entity> &event) { }

        virtual void ApplyEvent(const AbilityCast<Entity> &event) { }

        virtual void ApplyEvent(AbilityPreHit<AbilityAttribute, Entity> &event) { }

        virtual void ApplyEvent(const AbilityHit<Entity> &event) { }

        virtual void ApplyEvent(const AbilityMiss<Entity> &event) { }
    };

    template<class AbilityAttribute, class Entity>
    class Bus
    {
    private:
        std::vector<Handler<AbilityAttribute, Entity> *> handlers { };

    public:
        void AddHandler(const Handler<AbilityAttribute, Entity> &handler);

        void RemoveHandler(const Handler<AbilityAttribute, Entity> &handler);

        template<class T>
        T PublishEvent(T &event) const;
    };
}
