#ifndef ELF_CRAFTER_ELF32_VERSION_HPP
#define ELF_CRAFTER_ELF32_VERSION_HPP

#include "config.hpp"
#include "elf32/types.hpp"
#include "utility/lonifier/lonifier.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        enum struct enum_elf_version : elf32_word
        {
            NONE,
            CURRENT,
        };

        const lon_type* operator|(enum_elf_version elf_version, const lonifier& l);
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif
#endif