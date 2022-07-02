#include <utility>

#include "Source.h"

using namespace Combat;

template<class Entity>
Source<Entity>::Source(const Entity *caster, std::string name)
        : caster { caster }, name { std::move(name) }
{
}

template<class Entity>
bool Source<Entity>::operator==(const Source<Entity> &other) const
{
    return caster == other.caster && name == other.name;
}
