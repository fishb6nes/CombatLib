#include "Source.h"

using namespace Combat;

Source::Source(const std::string &&name, int id)
        : name { std::make_shared<const std::string>(name) }, id { id }
{
}

bool Source::operator==(const Source &other) const
{
    return id == other.id && name == other.name;
}
