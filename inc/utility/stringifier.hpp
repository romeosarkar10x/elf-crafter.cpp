#ifndef ELF_CRAFTER_STRINGIFIER_HPP
#define ELF_CRAFTER_STRINGIFIER_HPP

#include <cstdint>
#include <string>
#include <utility>

#include "config.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    struct stringifier
    {
        stringifier();
        stringifier(uint16_t lon_indent_width);

        uint16_t get_lon_indent_width() const;
        // uint16_t set_lon_indent_width(uint16_t lon_indent_width);

        void increment_depth() const;
        void decrement_depth() const;

        uint16_t get_depth() const;

        template <typename T, typename U = decltype(std::to_string(std::declval<T>()))>
        friend const std::string operator|(T value, const stringifier& s)
        {
            return std::to_string(value);
        }

    private:
        uint16_t m_lon_indent_width;

        mutable uint16_t m_depth = 0u;
    };
#ifdef PROJECT_NAMESPACE
}
#endif

#endif