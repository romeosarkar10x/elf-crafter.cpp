#ifndef ELF_TYPES
#define ELF_TYPES

#include <cstdint>

namespace elf_crafter
{
    typedef uint32_t elf32_address;
    typedef uint16_t elf32_half;

    typedef uint32_t elf32_offset;

    typedef int32_t elf32_signed_word;
    typedef uint32_t elf32_word;

    typedef uint8_t elf32_unsigned_char;
} // namespace elf_crafter

#endif