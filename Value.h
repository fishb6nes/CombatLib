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
        Source<Entity> source;
        std::vector<Modifier<Entity>> modifiers;

        float base;
        float percent;
        float flat;

    public:
        Value(Source<Entity> source, float base);

        inline Source<Entity> GetSource() const { return source; }

        inline const std::vector<Modifier<Entity>> &GetModifiers() const { return modifiers; }

        inline float GetBase() const { return base; }

    public:
        float ComputeValue() const;

        void AddModifier(const Modifier<Entity> &modifier);
    };
}
