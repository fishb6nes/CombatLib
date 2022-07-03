#pragma once

#include <string>
#include <utility>

namespace Combat
{
    class Source
    {
    private:
        int type;
        std::string name;
        Source *parent;

    public:
        Source(int type, std::string name, Source *parent = nullptr)
                : type { type }, name { std::move(name) }, parent { parent } { }

        inline int GetCombatType() const { return type; }

        inline const std::string &GetCombatName() const { return name; }

        inline Source *GetCombatParent() const { return parent; }
    };
}
