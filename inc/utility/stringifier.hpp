#ifndef ELF_CRAFTER_STRINGIFIER_HPP
#define ELF_CRAFTER_STRINGIFIER_HPP

#include <string>
#include <type_traits>
#include <utility>

#include "config.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    struct stringifier
    {
        stringifier();

        template <typename T, typename U = decltype(std::to_string(std::declval<T>()))>
        friend const std::string operator|(T value, const stringifier& s)
        {
            return std::to_string(value);
        }
    };
#ifdef PROJECT_NAMESPACE
}
#endif

#endif