#pragma once

#include <string>

#include "AbilitySnapshot.h"
#include "../Source.h"

namespace Combat
{
    class Ability
    {
    private:
        const AbilitySnapshot &snapshot;
        const Source          &caster;

    public:
        Ability(const AbilitySnapshot &snapshot, const Source &caster)
                : snapshot(snapshot), caster(caster) { }

    public:
        class Factory { };
    };
}
