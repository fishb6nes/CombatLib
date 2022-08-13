#pragma once

#include <set>
#include <string_view>

#include "Modifier.h"

namespace Combat
{
    class Attribute
    {
    private:
        std::string_view name;
        std::set<Modifier> modifiers;

        float flat = 0;
        float percent = 1;
        float cache = 0;

    public:
        explicit Attribute(std::string_view name)
                : name { name } { }

        inline std::string_view GetName() const { return name; }

        inline const std::set<Modifier> &GetModifiers() const { return modifiers; }

        inline float GetValue() const { return cache; }

    public:
        void AddModifier(const Modifier &modifier);

        void RemoveModifier(const Modifier &modifier);
    };
}
