#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "Modifier.h"

namespace Combat
{
    class Attribute
    {
    private:
        std::string name;
        std::vector<Modifier> modifiers { };

        float flat = 0;
        float percent = 1;
        float cache = 0;

    public:
        explicit Attribute(std::string name) : name { std::move(name) } { }

        inline const std::string &GetName() const { return name; }

        inline const std::vector<Modifier> &GetModifiers() const { return modifiers; }

        inline float GetValue() const { return cache; }

    public:
        void AddModifier(const Modifier &modifier)
        {
            flat += modifier.flat;
            percent += modifier.percent;
            cache = flat * percent;

            modifiers.push_back(modifier);
        }

        void RemoveModifier(const Modifier &modifier)
        {
            auto predicate = [modifier](auto it) { return it == modifier; };
            auto index = std::find_if(modifiers.begin(), modifiers.end(), predicate);
            if (index != modifiers.end())
            {
                flat -= modifier.flat;
                percent -= modifier.percent;
                cache = flat * percent;

                modifiers.erase(index);
            }
        }
    };
}
