#pragma once

#include "Source.h"

namespace Combat
{
    struct Modifier
    {
        Source *source;
        float flat;
        float percent;

        Modifier() = delete;

        inline static Modifier Flat(Source *source, float modifier)
        {
            return { source, modifier, 0 };
        }

        inline static Modifier Percent(Source *source, float modifier)
        {
            return { source, 0, modifier };
        }

        inline bool operator==(const Modifier &other) const
        {
            return source == other.source && flat == other.flat && percent == other.percent;
        }

        inline bool operator<(const Modifier &other) const
        {
            return source < other.source || flat < other.flat || percent < other.percent;
        }
    };
}
