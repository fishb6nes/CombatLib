#pragma once

#include <cassert>
#include <set>

#include "Modifier.h"

namespace Combat
{
    class Attribute
    {
    private:
        std::string_view name;
        std::set<Modifier> modifiers;

        float flatModifier = 0;
        float percentModifier = 1;
        float cachedValue = 0;

    public:
        explicit Attribute(std::string_view name)
                : name { name } { }

        inline std::string_view
        GetName() const { return name; }

        inline const std::set<Modifier> &
        GetModifiers() const { return modifiers; }

        inline float
        GetValue() const { return cachedValue; }

    public:
        void
        AddModifier(const Modifier &modifier)
        {
            bool inserted = modifiers.insert(modifier).second;
            assert(inserted);

            flatModifier += modifier.flatModifier;
            percentModifier += modifier.percentModifier;
            cachedValue = flatModifier * percentModifier;
        }

        void
        RemoveModifier(const Modifier &modifier)
        {
            bool erased = modifiers.erase(modifier);
            assert(erased);

            flatModifier -= modifier.flatModifier;
            percentModifier -= modifier.percentModifier;
            cachedValue = flatModifier * percentModifier;
        }
    };
}
