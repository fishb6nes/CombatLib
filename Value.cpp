#include "Value.h"

using namespace Combat;

template<class Entity>
Value<Entity>::Value(Source<Entity> source, float base)
        : source { source }, base { base }
{
}

template<class Entity>
float Value<Entity>::ComputeValue() const
{
    return base * percent + flat;
}

template<class Entity>
const std::vector<Modifier<Entity>> &Value<Entity>::ViewModifiers() const
{
    return modifiers;
}

template<class Entity>
void Value<Entity>::AddModifier(const Modifier<Entity> &modifier)
{
    percent += modifier.percent;
    flat += modifier.flat;

    modifiers.push_back(modifier);
}
