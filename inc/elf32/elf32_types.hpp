#ifndef ELF_CRAFTER_ELF32_TYPES_HPP
#define ELF_CRAFTER_ELF32_TYPES_HPP

#include <cstdint>

#include "config.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        typedef uint32_t elf32_address;
        typedef uint16_t elf32_half;

        typedef uint32_t elf32_offset;

        typedef int32_t  elf32_signed_word;
        typedef uint32_t elf32_word;

        typedef uint8_t elf32_unsigned_char;
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
} // namespace elf_crafter
#endif

#endif