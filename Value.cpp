#include "Value.h"

using namespace Combat;

Value::Value(const Source &source, float base)
        : source { source }
        , base { base }
{
}

inline float Value::ComputeValue() const
{
    return base * percent + flat;
}

inline const std::vector<Modifier> &Value::ViewModifiers() const
{
    return modifiers;
}

void Value::AddModifier(const Modifier &modifier)
{
    percent += modifier.percent;
    flat += modifier.flat;

    modifiers.push_back(modifier);
}
