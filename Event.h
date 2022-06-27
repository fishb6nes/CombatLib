#pragma once

#include <map>
#include <string>
#include <vector>

#include "Modifier.h"

namespace Combat
{
    namespace Event
    {
        template<class Event, class Attribute>
        static void AddModifierTo(Attribute attribute, Modifier modifier, Event event)
        {
            auto it = event.modifiers.find(attribute);
            if (it == event.modifiers.end())
            {
                std::vector<Modifier> v { };
                v.push_back(modifier);
                event.modifiers[attribute] = v;
            }
            else
            {
                it->second.push_back(modifier);
            }
        }

        template<class Entity, class Attribute>
        struct AbilityPreCast
        {
            std::string *ability;
            Entity *caster;
            std::map<Attribute, std::vector<Modifier>> *modifiers;

            bool isCancelled;
            bool isExplicitlyAllowed;
        };

        template<class Entity, class Attribute>
        struct AbilityCast
        {
            std::string *const ability;
            Entity *const caster;
        };

        template<class Entity, class Attribute>
        struct AbilityPreHit
        {
            std::string *const ability;
            Entity *const caster;
            Entity *const target;
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

        template<class Entity, class Attribute>
        class Handler
        {
        public:
            virtual void ApplyEvent(AbilityPreCast<Entity, Attribute> &event) { }

            virtual void ApplyEvent(const AbilityCast<Entity, Attribute> &event) { }

            virtual void ApplyEvent(AbilityPreHit<Entity, Attribute> &event) { }

            virtual void ApplyEvent(const AbilityHit<Entity> &event) { }

            virtual void ApplyEvent(const AbilityMiss<Entity> &event) { }
        };

        template<class Entity, class Attribute>
        class Bus
        {
        private:
            std::vector<const Handler<Entity, Attribute> *> handlers { };

        public:
            void AddHandler(const Handler<Entity, Attribute> &handler);

            void RemoveHandler(const Handler<Entity, Attribute> &handler);

            template<class T>
            T PublishEvent(T &event) const;
        };
    }
}
