#pragma once

namespace Combat
{
    namespace Event
    {
        class Bus;
    }

    struct Source
    {
        int type;
        void *object;
        Event::Bus *status;

        Source(int type, void *object, Event::Bus *status)
                : type { type }, object { object }, status { status } { }

        inline bool operator==(const Source &other) const
        {
            return type == other.type && object == other.object;
        }
    };
}
