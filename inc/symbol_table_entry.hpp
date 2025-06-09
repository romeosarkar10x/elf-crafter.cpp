#ifndef ELF_CRAFTER_SYMBOL_TABLE_ENTRY
#define ELF_CRAFTER_SYMBOL_TABLE_ENTRY

#include "elf_types.hpp"
#include "section.hpp"

namespace elf_crafter
{
    struct symbol_table_entry
    {
        enum struct enum_symbol_type : uint8_t
        {
            NO_TYPE,
            OBJECT,

            FUNCTION,
            SECTION,
            FILE,
            PROCESSOR_SPECIFIC_SEMANTICS_LOW  = 13u,
            PROCESSOR_SPECIFIC_SEMANTICS_HIGH = 15u,
        };

        enum struct enum_symbol_binding : uint8_t
        {
            LOCAL,
            GLOBAL,
            WEAK,
            PROCESSOR_SPECIFIC_SEMANTICS_LOW  = 13u,
            PROCESSOR_SPECIFIC_SEMANTICS_HIGH = 15u,
        };

    private:
        elf32_word          m_name_string_table_index;
        elf32_address       m_value;
        elf32_word          m_size;
        elf32_unsigned_char m_info;
        elf32_unsigned_char m_other;
        elf32_unsigned_char m_section_header_index;
    };

} // namespace elf_crafter

#endif