#include <algorithm>
#include <utility>

#include "Attribute.h"

using namespace Combat;

template<class Entity>
Attribute<Entity>::Attribute(std::string name)
        : name { std::move(name) }, modifiers { }, flat { 0 }, percent { 1 }, cache { 0 }
{
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
