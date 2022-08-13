#pragma once

#include <map>
#include <memory>
#include <string_view>
#include <vector>

#include "./math.h"
#include "Entity.h"
#include "Modifier.h"

#ifndef COMBAT_ABILITY_TYPE
#define COMBAT_ABILITY_TYPE 1
#endif

namespace Combat
{
    class Projectile;

    class Ability : public Source
    {
    public:
        typedef int Attribute;
        typedef std::map<Attribute, float> Config;
        typedef std::map<Attribute, std::vector<Modifier>> Modifiers;

    public:
        Ability(std::string_view name, Entity &caster, int type = COMBAT_ABILITY_TYPE)
                : Source(type, name, &caster) { }

        inline Entity &GetCaster() const { return static_cast<Entity &>(*parent); }

    public:
        virtual bool OnEntityHit(Entity &entity) = 0;

        virtual bool OnEntityMiss(Entity &entity) = 0;

        virtual void OnProjectileOutOfRange(Projectile &projectile) { }
    };
}
