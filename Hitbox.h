#pragma once

#include <vector>

#include "Entity.h"
#include "EntityService.h"

namespace Combat
{
    class Hitbox
    {
    public:
        virtual std::vector<Entity> GetEntityCollisions(EntityService &entityService) = 0;

        virtual std::vector<int> GetWorldCollisions() = 0;
    };

    class SphericalHitbox : public Hitbox
    {
    private:
        float radius;

    public:
        explicit SphericalHitbox(float radius)
                : radius { radius } { }

        std::vector<Entity> GetEntityCollisions(EntityService &entityService) override
        {
            return { }; // TODO
        }

        std::vector<int> GetWorldCollisions() override
        {
            return { }; // TODO
        }
    };

    class VoidHitbox : public Hitbox
    {
    public:
        std::vector<Entity> GetEntityCollisions(EntityService &entityService) override { return { }; }

        std::vector<int> GetWorldCollisions() override { return { }; }
    };
}
