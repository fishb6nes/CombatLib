#pragma once

#include <string>

#include "Event.h"
#include "Source.h"

#include "Ability.h"

namespace Combat
{
    namespace Ability
    {
        template<class Entity, class Attribute>
        class Service
        {
        private:
            const Event::Bus<Entity, Attribute> &eventBus;

        public:
            explicit Service(const Event::Bus<Entity, Attribute> &eventBus);

        public:
            Snapshot *PublishPreCastEvent(std::string *ability, Entity *caster) const;

            bool PublishHitEvents(std::string ability, const Entity &caster, const Entity &target) const;
        };
    }
}
