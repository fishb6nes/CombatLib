#pragma once

#include <string>

namespace Combat
{
    class AbilitySnapshot
    {
    public:
        explicit AbilitySnapshot(std::string &&name) : name(name) { }

        const std::string name;
    };
}
