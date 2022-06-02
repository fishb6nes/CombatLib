#pragma once

#include "Ability.h"

namespace Combat
{
    class ChildAbility
    {
    public:
        class Factory : public Ability::Factory
        {
        public:
            virtual ChildAbility Create(int parent, int snapshot, int metadata) = 0;
        };
    };
}
