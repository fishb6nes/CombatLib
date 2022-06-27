#pragma once

#include <memory>
#include <string>

namespace Combat
{
    struct Source
    {
        std::shared_ptr<const std::string> name;
        int id;

        Source(const std::string &&name, int id);

        bool operator==(const Source &other) const;
    };
}
