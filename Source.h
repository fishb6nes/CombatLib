#pragma once

#include <string>

namespace Combat
{
    template<class Entity>
    class Source
    {
    private:
        Entity *caster;
        std::string name;

    public:
        Source(const Entity *caster, std::string name);

        bool operator==(const Source<Entity> &other) const;

        inline const Entity *GetCaster() const { return caster; }

        inline const std::string &GetName() const { return name; }
    };
}
