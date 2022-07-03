#pragma once

#include "Event.h"

namespace Combat::Status
{
    class Effect : public Source, Event::Handler
    {
    public:
        Effect(int type, std::string name, Source *parent)
                : Source(type, std::move(name), parent) { }
    };

    class Affectable : public Source
    {
    private:
        Event::Bus status { };

    public:
        Affectable(int type, std::string name, Source *parent)
                : Source(type, std::move(name), parent) { }

        inline Event::Bus &GetStatus() { return status; }
    };
}
