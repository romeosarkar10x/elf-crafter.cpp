#pragma once

#include <config.hpp>
#include <string>

#include <elf32/forward_declaration.hpp>
#include <elf32/type.hpp>

#include "symbol_table_entry_raw.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        struct symbol
        {
            symbol(
                section* section, const char* name, elf32_address value, elf32_word size,
                symbol_table_entry_raw::enum_symbol_type type, symbol_table_entry_raw::enum_symbol_binding binding
            );

            symbol(
                section* section, const char* name, elf32_word alignment, elf32_word size,
                symbol_table_entry_raw::enum_symbol_type type, symbol_table_entry_raw::enum_symbol_binding binding
            );

            friend const lon_type* operator|(const symbol& s, const lonifier& l);

        private:
            section*    m_section;
            std::string m_name;

            union
            {
                elf32_word    alignment;
                elf32_address value;
            } m_value_or_alignment;

            elf32_word m_size;

            symbol_table_entry_raw::enum_symbol_type    m_type    : 4u;
            symbol_table_entry_raw::enum_symbol_binding m_binding : 4u;
        };
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif
