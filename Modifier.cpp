#include "Modifier.h"

using namespace Combat;

Modifier Modifier::Flat(Source source, float modifier)
{
    return { std::move(source), modifier, 0 };
}

Modifier Modifier::Percent(Source source, float modifier)
{
    return { std::move(source), 0, modifier };
}

bool Modifier::operator==(const Modifier &other) const
{
    return flat == other.flat && percent == other.percent && source == other.source;
}
