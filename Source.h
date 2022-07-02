#pragma once

#include <string>

namespace Combat
{
    template<class Entity>
    struct Source
    {
        const Entity *caster;
        const std::string *name;

        Source(const Entity *caster, const std::string &name);

        bool operator==(const Source<Entity> &other) const;
    };
}
