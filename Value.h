#pragma once

#include <vector>

#include "Modifier.h"

namespace Combat
{
    class Value
    {
    private:
        Source *source;
        std::vector<Modifier> modifiers { };

        float base;
        float percent = 1;
        float flat = 0;
        float cache = 0;

    public:
        Value(Source *source, float base)
                : source { source }, base { base } { }

        inline Source *GetSource() const { return source; }

        inline const std::vector<Modifier> &GetModifiers() const { return modifiers; }

        inline float GetBase() const { return base; }

        inline float GetModified() const { return cache; }

    public:
        void AddModifier(const Modifier &modifier)
        {
            percent += modifier.percent;
            flat += modifier.flat;
            cache = base * percent + flat;

            modifiers.push_back(modifier);
        }
    };
}
