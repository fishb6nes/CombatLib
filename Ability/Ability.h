#pragma once

#include <map>
#include <vector>

#include "../Core/Modifier.h"
#include "../Entity/Entity.h"

#ifndef COMBAT_ABILITY_TYPE
#define COMBAT_ABILITY_TYPE 1
#endif

namespace Combat
{
    class Projectile;
}

namespace Combat
{
    class Ability : public Source
    {
    public:
        typedef int Attribute;
        typedef std::map<Attribute, float> Config;
        typedef std::map<Attribute, std::vector<Modifier>> Modifiers;

    public:
        Ability(std::string_view name, Entity &caster, int type = COMBAT_ABILITY_TYPE)
                : Source(type, name, &caster) { }

        inline Entity &
        GetCaster() const { return static_cast<Entity &>(*parent); }

    public:
        virtual bool
        OnEntityHit(const Entity &entity) = 0;

        virtual bool
        OnEntityMiss(const Entity &entity) = 0;

        virtual void
        OnProjectileOutOfRange(const int &projectile) { }
    };
}
