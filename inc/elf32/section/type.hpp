#ifndef ELF_CRAFTER_ELF32_SECTION_TYPE
#define ELF_CRAFTER_ELF32_SECTION_TYPE

#include <elf32/type.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        enum struct enum_section_type : elf32_word::type
        {
            NULL_TYPE,
            PROGRAM_BITS,
            SYMBOL_TABLE,
            STRING_TABLE,
            RELOCATION_WITH_ADDENDS,
            HASH,
            DYNAMIC,
            NOTE,
            NO_BITS,
            RELOCATION,
            LIB,
            DYNAMIC_SYMBOL,

            LO_PROC = 0x70000000u,
            HI_PROC = 0x7fffffffu,

            LO_USER = 0x80000000u,
            HI_USER = 0xffffffffu,
        };

        const lon_type* operator|(enum_section_type section_type, const lonifier& l);
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
}
#endif

#endif