#pragma once

#include <vector>

#include "Modifier.h"
#include "Source.h"

namespace Combat
{
    template<class Entity>
    class Value
    {
    private:
        float percent = 1;
        float flat = 0;

        std::vector<Modifier<Entity>> modifiers { };

    public:
        const Source<Entity> source;
        const float base;

        Value(Source<Entity> source, float base);

    public:
        [[nodiscard]] float ComputeValue() const;

        [[nodiscard]] const std::vector<Modifier<Entity>> &ViewModifiers() const;

        void AddModifier(const Modifier<Entity> &modifier);
    };
}
