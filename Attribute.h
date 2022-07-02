#pragma once

#include <string>
#include <vector>

#include "Modifier.h"

namespace Combat
{
    template<class Entity>
    class Attribute
    {
    private:
        std::string name;
        std::vector<Modifier<Entity>> modifiers;

        float flat;
        float percent;
        float cache;

    public:
        explicit Attribute(std::string name);

        inline const std::string &GetName() const { return name; }

        inline const std::vector<Modifier<Entity>> &GetModifiers() const { return modifiers; }

        inline float GetValue() const { return cache; }

    public:
        void AddModifier(const Modifier<Entity> &modifier);

        void RemoveModifier(const Modifier<Entity> &modifier);
    };
}
