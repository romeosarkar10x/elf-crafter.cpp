#pragma once

#include "config.hpp"
#include "elf32/type.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        struct symbol_table_entry_raw
        {
            enum struct enum_symbol_type : uint8_t
            {
                NO_TYPE,
                OBJECT,

                FUNCTION,
                SECTION,
                FILE,
                COMMON,
                THREAD_LOCAL_STORAGE,
                PROCESSOR_SPECIFIC_SEMANTICS_LOW  = 13u,
                PROCESSOR_SPECIFIC_SEMANTICS_HIGH = 15u,
            };

            friend const lon_type* operator|(enum_symbol_type symbol_type, const lonifier& l);

            enum struct enum_symbol_binding : uint8_t
            {
                LOCAL,
                GLOBAL,
                WEAK,

                PROCESSOR_SPECIFIC_SEMANTICS_LOW  = 13u,
                PROCESSOR_SPECIFIC_SEMANTICS_HIGH = 15u,
            };

            friend const lon_type* operator|(enum_symbol_binding symbol_binding, const lonifier& l);

            struct symbol_info
            {
                enum_symbol_binding get_symbol_binding() const;
                enum_symbol_type    get_symbol_type() const;

            private:
                enum_symbol_type    m_type    : 4u; // Lower nibble
                enum_symbol_binding m_binding : 4u; // Upper nibble
            };

            elf32_word          name_string_table_index;
            elf32_address       value;
            elf32_word          size;
            symbol_info         info;
            elf32_unsigned_char other;
            elf32_half          section_header_index;
        };
    } // namespace elf32
} // namespace elf_crafter
