#include "Value.h"

using namespace Combat;

Value::Value(Source *source, float base, const std::vector<Modifier> &modifiers)
        : source { source }, base { base }, baseModifiers { modifiers }
{
    for (auto modifier : modifiers)
    {
        UpdateCache(modifier);
    }
}

void Value::AddModifier(Modifier modifier)
{
    modifiers.push_back(modifier);
    UpdateCache(modifier);
}

void Value::UpdateCache(Modifier modifier)
{
    percent += modifier.percent;
    flat += modifier.flat;
    cache = base * percent + flat;
}
