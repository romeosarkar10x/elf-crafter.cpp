#pragma once

#include <cstdint>

#include <utility/lonifier/lonifier.hpp>

#include "config.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        // Wrapper around uint32_t (for better customization)

        template <typename DERIVED> struct crtp
        {
            friend const lon_type* operator|(const DERIVED& derived, const lonifier& l);
        };

        template <typename T> struct decorator
        {
            constexpr inline decorator() {}
            constexpr inline decorator(T value) : value(value) {}

            constexpr decorator& operator=(T value)
            {
                this->value = value;
                return *this;
            }

            constexpr operator T() const { return this->value; }

            constexpr decorator& operator=(const decorator& address)
            {
                this->value = address.value;
                return *this;
            }

            friend constexpr decorator operator+(const decorator& a, const decorator& b) { return (a.value + b.value); }

            T value;
            using type = T;
        };

        struct elf32_address : public decorator<uint32_t>, public crtp<elf32_address>
        {
            using decorator<uint32_t>::decorator;
        };
        struct elf32_offset : public decorator<uint32_t>, public crtp<elf32_offset>
        {
            using decorator<uint32_t>::decorator;
        };
        struct elf32_half : public decorator<uint16_t>, public crtp<elf32_half>
        {
            using decorator<uint16_t>::decorator;
        };
        struct elf32_signed_word : public decorator<int32_t>, public crtp<elf32_signed_word>
        {};
        struct elf32_word : public decorator<uint32_t>, public crtp<elf32_word>
        {
            using decorator<uint32_t>::decorator;
        };
        // typedef uint32_t elf32_address;
        // typedef uint32_t elf32_offset;

        // typedef int32_t  elf32_signed_word;
        // typedef uint32_t elf32_word;
        typedef uint8_t elf32_unsigned_char;
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
} // namespace elf_crafter
#endif