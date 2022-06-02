#pragma once

#include <memory>

#include "Ability.h"

namespace Combat
{
    class TargetlessAbility : public Ability
    {
    public:
        virtual bool OnHit(int target) = 0;

        virtual bool OnMiss(int target) = 0;

        virtual bool OnGrounded(int location) { return true; };

        virtual bool OnMaxRange(int location) { return true; };

    public:
        class Factory : public Ability::Factory
        {
        public:
            virtual std::unique_ptr<TargetlessAbility> Create(int snapshot, int caster) = 0;
        };
    };
}
