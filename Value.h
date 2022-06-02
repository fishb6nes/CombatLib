#pragma once

#include <vector>

#include "Modifier.h"
#include "Source.h"

namespace Combat
{
    class Value
    {
    private:
        float percent = 1;
        float flat = 0;

        std::vector<Modifier> modifiers { };

    public:
        const Source source;
        const float base;

        Value(const Source &source, float base);

    public:
        inline float ComputeValue() const;

        inline const std::vector<Modifier> &ViewModifiers() const;

        void AddModifier(const Modifier &modifier);
    };
}
