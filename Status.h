#pragma once

#include <string_view>

#include "Event.h"

namespace Combat::Status
{
    class Effect : public Source, Event::Handler
    {
    public:
        Effect(int type, std::string_view name, Source *parent)
                : Source(type, name, parent) { }
    };

    class Affectable : public Source
    {
    private:
        Event::Bus status { };

    public:
        Affectable(int type, std::string_view name, Source *parent)
                : Source(type, name, parent) { }

        inline Event::Bus &GetCombatStatus() { return status; }
    };
}
