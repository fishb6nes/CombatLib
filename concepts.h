#pragma once

#include <concepts>

namespace Combat
{
    template<typename T, typename ... U>
    concept same_as_any = (std::same_as<T, U> || ...);
}
