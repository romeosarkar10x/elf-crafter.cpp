#ifndef ELF_CRAFTER_RELOCATION_ENTRY_HPP
#define ELF_CRAFTER_RELOCATION_ENTRY_HPP

#include "config.hpp"
#include "elf32/types.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
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

    } // namespace elf32
#ifdef PROJECT_NAMESPACE
}
#endif

#endif