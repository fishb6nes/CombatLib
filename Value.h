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

        float percent = 1;
        float flat = 0;
        float cache = 0;

    public:
        Value(Source *source, float base, const std::vector<Modifier> &modifiers = { });

        inline Source *GetSource() const { return source; }

        inline float GetBase() const { return base; }

        inline Modifiers GetModifiers() const { return std::make_pair(baseModifiers, modifiers); }

        inline float GetModified() const { return cache; }

    public:
        void AddModifier(Modifier modifier);

    private:
        void UpdateCache(Modifier modifier);
    };
}
