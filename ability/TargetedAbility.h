#pragma once

#include <memory>

#include "Ability.h"

namespace Combat
{
    class TargetedAbility : public Ability
    {
    public:
        virtual bool OnHit(int target) = 0;

        virtual bool OnMiss(int target) = 0;

    public:
        class Factory : public Ability::Factory
        {
        public:
            virtual std::unique_ptr<TargetedAbility> Create(int snapshot, int caster, int entityTarget) = 0;

            virtual std::unique_ptr<TargetedAbility> Create(int snapshot, int caster, float groundTarget) = 0;
        };
    };
}
