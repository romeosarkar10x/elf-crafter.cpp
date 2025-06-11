#ifndef ELF_CRAFTER_RELOCATION_ENTRY_HPP
#define ELF_CRAFTER_RELOCATION_ENTRY_HPP

#include "types.hpp"

namespace elf_crafter
{
    struct relocation
    {
    private:
        elf32_address offset;
        elf32_word    info;
    };

    struct relocation_with_addend
    {
    private:
        elf32_address     offset;
        elf32_word        info;
        elf32_signed_word addend;
    };
} // namespace elf_crafter

#endif