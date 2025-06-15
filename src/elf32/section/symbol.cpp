#include <elf32/section/symbol.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        symbol::symbol(
            section* section, const char* name, elf32_address value, elf32_word size,
            symbol_table_entry_raw::enum_symbol_type type, symbol_table_entry_raw::enum_symbol_binding binding
        )
            : m_section{section},
              m_name{name},
              m_value_or_alignment{.value = value},
              m_size{size},
              m_type{type},
              m_binding{binding}
        {}

        symbol::symbol(
            section* section, const char* name, elf32_word alignment, elf32_word size,
            symbol_table_entry_raw::enum_symbol_type type, symbol_table_entry_raw::enum_symbol_binding binding
        )
            : m_section{section},
              m_name{name},
              m_value_or_alignment{.alignment = alignment},
              m_size{size},
              m_type{type},
              m_binding{binding}
        {}

        const lon_type* operator|(const symbol& symbol, const lonifier& l)
        {
            lon_object* lo = new lon_object;

            if (!symbol.m_name.empty()) {
                lo->set_key("Name", new lon_string(symbol.m_name));
            }

            lo->set_key("Type", symbol.m_type | l);
            lo->set_key("Binding", symbol.m_binding | l);

            if (symbol.m_section) {
                lo->set_key("Section", symbol.m_section | l);
            }

            if (symbol.m_section == nullptr && symbol.m_type == symbol_table_entry_raw::enum_symbol_type::COMMON) {
                lo->set_key("Alignment", symbol.m_value_or_alignment.alignment | l);
            } else {
                lo->set_key("Value", symbol.m_value_or_alignment.value | l);
            }

            if (symbol.m_size) {
                lo->set_key("Size", symbol.m_size | l);
            }

            return lo;
        }
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif
