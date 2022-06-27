#pragma once

#include <string>
#include <vector>

#include "Modifier.h"

namespace Combat
{
    class Attribute
    {
    private:
        float flat = 0;
        float percent = 1;
        float cache = 0;

        std::vector<Modifier> modifiers { };

    public:
        const std::string name;

        explicit Attribute(std::string &&name);

    public:
        inline float GetValue() const;

        inline const std::vector<Modifier> &ViewModifiers() const;

        void AddModifier(const Modifier &modifier);

        void RemoveModifier(const Modifier &modifier);
    };
}
