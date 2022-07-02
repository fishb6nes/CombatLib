#pragma once

#include "Source.h"

namespace Combat
{
    template<class Entity>
    struct Modifier
    {
        Source<Entity> source;
        float flat;
        float percent;

        Modifier() = delete;

        static Modifier<Entity> Flat(Source<Entity> source, float modifier);

        static Modifier<Entity> Percent(Source<Entity> source, float modifier);

        bool operator==(const Modifier<Entity> &other) const;
    };
}
