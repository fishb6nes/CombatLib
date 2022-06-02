#pragma once

#include <memory>

#include "Ability.h"

namespace Combat
{
    class GroundTargetAbility : public Ability
    {
    public:
        virtual void OnHit(int target) = 0;

        virtual void OnMiss(int target) = 0;

    public:
        class Factory : public Ability::Factory
        {
        public:
            virtual std::unique_ptr<GroundTargetAbility> Create(int snapshot, int caster, float target) = 0;
        };
    };
}
