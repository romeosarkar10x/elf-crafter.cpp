#ifndef ELF_CRAFTER_COMPARE_HPP
#define ELF_CRAFTER_COMPARE_HPP

#include <type_traits>

#include "config.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    template <typename T, typename U>
        requires std::is_fundamental_v<T> && std::is_enum_v<U>
    bool operator==(T a, U b)
    {
        return (a == static_cast<T>(b));
    }

    template <typename T, typename U>
        requires std::is_enum_v<T> && std::is_fundamental_v<U>
    bool operator==(T a, U b)
    {
        return (static_cast<U>(a) == b);
    }

    template <typename T, typename U>
    std::enable_if_t<std::conjunction_v<std::is_enum<T>, std::is_fundamental<U>>, bool> operator!=(
        T a, U b
    )
    {
        return (a != static_cast<T>(b));
    }

    template <typename T, typename U>
    std::enable_if_t<std::conjunction_v<std::is_fundamental<T>, std::is_enum<U>>, bool> operator!=(
        T a, U b
    )
    {
        return (static_cast<U>(a) != b);
    }

#ifdef PROJECT_NAMESPACE
}

#define DEFINE_COMPARISON_OPERATORS(type_A, type_B)                                                \
    template bool operator==(type_A, type_B);                                                      \
    template bool operator==(type_B, type_A);                                                      \
    template bool operator!=(type_A, type_B);                                                      \
    template bool operator!=(type_B, type_A);
#endif
#endif