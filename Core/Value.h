#pragma once

#include <vector>

#include "Modifier.h"

namespace Combat
{
    class Value
    {
    private:
        Source *source;
        float baseValue;
        std::vector<Modifier> modifiers;

        float percentModifier = 1;
        float flatModifier = 0;
        float cachedValue = 0;

    public:
        Value(Source *source, float base, const std::vector<Modifier> &modifiers = { })
                : source { source }, baseValue { base }, modifiers { modifiers }
        {
            for (auto modifier : modifiers) UpdateCache(modifier);
        }

        inline Source *
        GetSource() const { return source; }

        inline float
        GetBaseValue() const { return baseValue; }

        inline const std::vector<Modifier> &
        GetModifiers() const { return modifiers; }

        inline float
        GetModifiedValue() const { return cachedValue; }

    public:
        void
        AddModifier(Modifier modifier)
        {
            modifiers.push_back(modifier);
            UpdateCache(modifier);
        }

    private:
        inline void
        UpdateCache(Modifier modifier)
        {
            percentModifier += modifier.percentModifier;
            flatModifier += modifier.flatModifier;
            cachedValue = baseValue * percentModifier + flatModifier;
        }
    };
}
