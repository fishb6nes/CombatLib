#include <algorithm>

#include "Attribute.h"

using namespace Combat;

template<class Entity>
Attribute<Entity>::Attribute(std::string &&name)
        : name { name }
{
}

template<class Entity>
float Attribute<Entity>::GetValue() const
{
    return cache;
}

template<class Entity>
const std::vector<Modifier<Entity>> &Attribute<Entity>::ViewModifiers() const
{
    return modifiers;
}

template<class Entity>
void Attribute<Entity>::AddModifier(const Modifier<Entity> &modifier)
{
    flat += modifier.flat;
    percent += modifier.percent;
    cache = flat * percent;

    modifiers.push_back(modifier);
}

template<class Entity>
void Attribute<Entity>::RemoveModifier(const Modifier<Entity> &modifier)
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
