#pragma once

#include <string_view>

#include "Source.h"

namespace Combat
{
    class StatusEffect : public Source
    {
    public:
        StatusEffect(int type, std::string_view name, Source *parent)
                : Source(type, name, parent) { }
    };
}
