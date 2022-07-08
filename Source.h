#pragma once

#include <string_view>

namespace Combat
{
    class Source
    {
    private:
        int type;
        std::string_view name;
        Source *parent;

    public:
        Source(int type, std::string_view name, Source *parent = nullptr)
                : type { type }, name { name }, parent { parent } { }

        inline int GetCombatType() const { return type; }

        inline std::string_view GetCombatName() const { return name; }

        inline Source *GetCombatParent() const { return parent; }
    };
}
