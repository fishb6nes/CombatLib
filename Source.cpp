#include "Source.h"

using namespace Combat;

template<class Entity>
Source<Entity>::Source(const Entity *caster, const std::string &name)
        : caster { caster }, name { &name }
{
}

template<class Entity>
bool Source<Entity>::operator==(const Source<Entity> &other) const
{
    return caster == other.caster && name == other.name;
}
