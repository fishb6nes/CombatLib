#pragma once

#include <vector>

#include "Modifier.h"

namespace Combat
{
    class Value
    {
    public:
        typedef std::pair<const std::vector<Modifier> &, const std::vector<Modifier> &> Modifiers;

    private:
        Source *source;
        float base;
        const std::vector<Modifier> &baseModifiers;
        std::vector<Modifier> modifiers;

        float percent;
        float flat;
        float cache;

    public:
        Value(Source *source, float base, const std::vector<Modifier> &modifiers = { })
                : source { source }, base { base }, baseModifiers { modifiers }, modifiers { },
                  percent { 1 }, flat { 0 }, cache { 0 }
        {
            for (auto modifier : modifiers)
            {
                UpdateCache(modifier);
            }
        }

        inline Source *GetSource() const { return source; }

        inline float GetBase() const { return base; }

        inline Modifiers GetModifiers() const { return std::make_pair(baseModifiers, modifiers); }

        inline float GetModified() const { return cache; }

    public:
        void AddModifier(Modifier modifier)
        {
            UpdateCache(modifier);
            modifiers.push_back(modifier);
        }

    private:
        void UpdateCache(Modifier modifier)
        {
            percent += modifier.percent;
            flat += modifier.flat;
            cache = base * percent + flat;
        }
    };
}
