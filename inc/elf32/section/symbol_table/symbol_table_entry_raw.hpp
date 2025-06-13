#ifndef ELF_CRAFTER_SYMBOL_TABLE_ENTRY
#define ELF_CRAFTER_SYMBOL_TABLE_ENTRY

#include "config.hpp"
#include "elf32/section/section.hpp"
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
    } // namespace elf32
} // namespace elf_crafter

#endif