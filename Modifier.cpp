#include "Modifier.h"

using namespace Combat;

template<class Entity>
Modifier<Entity> Modifier<Entity>::Flat(Source<Entity> source, float modifier)
{
    return { source, modifier, 0 };
}

template<class Entity>
Modifier<Entity> Modifier<Entity>::Percent(Source<Entity> source, float modifier)
{
    return { source, 0, modifier };
}

template<class Entity>
bool Modifier<Entity>::operator==(const Modifier<Entity> &other) const
{
    return flat == other.flat && percent == other.percent && source == other.source;
}
