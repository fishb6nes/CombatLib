#pragma once

#include <set>
#include <string>
#include <utility>

#include "Modifier.h"

namespace Combat
{
    class Attribute
    {
    private:
        std::string name;
        std::set<Modifier> modifiers { };

        float flat = 0;
        float percent = 1;
        float cache = 0;

    public:
        explicit Attribute(std::string name)
                : name { std::move(name) } { }

        inline const std::string &GetName() const { return name; }

        inline const std::set<Modifier> &GetModifiers() const { return modifiers; }

        inline float GetValue() const { return cache; }

    public:
        void AddModifier(const Modifier &modifier)
        {
            if (modifiers.insert(modifier).second)
            {
                flat += modifier.flat;
                percent += modifier.percent;
                cache = flat * percent;
            }
        }

        void RemoveModifier(const Modifier &modifier)
        {
            if (modifiers.erase(modifier))
            {
                flat -= modifier.flat;
                percent -= modifier.percent;
                cache = flat * percent;
            }
        }
    };
}
