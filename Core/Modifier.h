#pragma once

#include "Source.h"

namespace Combat
{
    struct Modifier
    {
        Source *source;
        float flatModifier;
        float percentModifier;

        inline static Modifier
        Flat(Source *source, float flatModifier)
        {
            return { source, flatModifier, 0 };
        }

        inline static Modifier
        Percent(Source *source, float percentModifier)
        {
            return { source, 0, percentModifier };
        }

        inline bool
        operator==(const Modifier &other) const
        {
            return source == other.source
                   && flatModifier == other.flatModifier
                   && percentModifier == other.percentModifier;
        }

        inline bool
        operator<(const Modifier &other) const
        {
            return source < other.source
                   || flatModifier < other.flatModifier
                   || percentModifier < other.percentModifier;
        }
    };
}
