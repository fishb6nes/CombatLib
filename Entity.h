#pragma once

#include <string_view>

#include "Event.h"
#include "Source.h"

namespace Combat
{
    class Entity : public Source
    {
    private:
        int id;
        Event::Bus status { };

    public:
        Entity(int type, std::string_view name, Source *parent, int id)
                : Source(type, name, parent), id { id } { }

        inline int GetCombatId() const { return id; }

        inline Event::Bus &GetCombatStatus() { return status; }
    };
}
