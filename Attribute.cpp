#include <algorithm>

#include "Attribute.h"

using namespace Combat;

Attribute::Attribute(std::string &&name)
        : name { name }
{
}

inline float Attribute::GetValue() const
{
    return cache;
}

inline const std::vector<Modifier> &Attribute::ViewModifiers() const
{
    return modifiers;
}

void Attribute::AddModifier(const Modifier &modifier)
{
    flat += modifier.flat;
    percent += modifier.percent;
    cache = flat * percent;

    modifiers.push_back(modifier);
}

void Attribute::RemoveModifier(const Modifier &modifier)
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
