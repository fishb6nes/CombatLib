#include "Attribute.h"

using namespace Combat;

void Attribute::AddModifier(const Modifier &modifier)
{
    if (modifiers.insert(modifier).second)
    {
        flat += modifier.flat;
        percent += modifier.percent;
        cache = flat * percent;
    }
}

void Attribute::RemoveModifier(const Modifier &modifier)
{
    if (modifiers.erase(modifier))
    {
        flat -= modifier.flat;
        percent -= modifier.percent;
        cache = flat * percent;
    }
}
