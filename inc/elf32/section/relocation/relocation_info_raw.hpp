#pragma once

#include <config.hpp>

#include <elf32/type.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        enum enum_relocation_type : elf32_unsigned_char
        {
            I386_NONE,
            I386_DEFAULT,
            I386_PROGAM_COUNTER,
            I386_GLOBAL_OFFSET_TABLE,
            I386_PROCEDURE_LINKAGE_TABLE,
        };

        struct relocation_info_raw
        {
            enum_relocation_type type               : 8;
            elf32_word::type     symbol_table_index : 24;
        };

    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif