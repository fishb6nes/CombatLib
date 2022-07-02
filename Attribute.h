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
        float flat = 0;
        float percent = 1;
        float cache = 0;

        std::vector<Modifier<Entity>> modifiers { };

    public:
        const std::string name;

        explicit Attribute(std::string &&name);

    public:
        [[nodiscard]] float GetValue() const;

        [[nodiscard]] const std::vector<Modifier<Entity>> &ViewModifiers() const;

        void AddModifier(const Modifier<Entity> &modifier);

        void RemoveModifier(const Modifier<Entity> &modifier);
    };
}
