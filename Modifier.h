#pragma once

#include "Source.h"

namespace Combat
{
    struct Modifier
    {
        Source source;
        float flat;
        float percent;

        Modifier() = delete;

        static Modifier Flat(Source source, float modifier);

        static Modifier Percent(Source source, float modifier);

        bool operator==(const Modifier &other) const;
    };
}
