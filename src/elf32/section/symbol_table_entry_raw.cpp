#include <elf32/section/symbol_table_entry_raw.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        symbol_table_entry_raw::enum_symbol_binding symbol_table_entry_raw::symbol_info::get_symbol_binding() const
        {
            return m_binding;
        }

        symbol_table_entry_raw::enum_symbol_type symbol_table_entry_raw::symbol_info::get_symbol_type() const
        {
            return m_type;
        }

        const lon_type* operator|(symbol_table_entry_raw::enum_symbol_type symbol_type, const lonifier& l)
        {
            switch (symbol_type) {
            case symbol_table_entry_raw::enum_symbol_type::NO_TYPE:
                return new lon_string("No type");

            case symbol_table_entry_raw::enum_symbol_type::OBJECT:
                return new lon_string("Object");

            case symbol_table_entry_raw::enum_symbol_type::FUNCTION:
                return new lon_string("Function");

            case symbol_table_entry_raw::enum_symbol_type::SECTION:
                return new lon_string("Section");

            case symbol_table_entry_raw::enum_symbol_type::FILE:
                return new lon_string("File");

            case symbol_table_entry_raw::enum_symbol_type::COMMON:
                return new lon_string("Common");

            case symbol_table_entry_raw::enum_symbol_type::THREAD_LOCAL_STORAGE:
                return new lon_string("Thread-local storage");

            default:
                throw std::runtime_error("Unhandled `symbol_type`");
            }

            throw std::runtime_error("Invalid `symbol_type`");
        }

        const lon_type* operator|(symbol_table_entry_raw::enum_symbol_binding symbol_binding, const lonifier& l)
        {
            switch (symbol_binding) {
            case symbol_table_entry_raw::enum_symbol_binding::LOCAL:
                return new lon_string("Local");

            case symbol_table_entry_raw::enum_symbol_binding::GLOBAL:
                return new lon_string("Global");

            case symbol_table_entry_raw::enum_symbol_binding::WEAK:
                return new lon_string("Weak");

            default:
                throw std::runtime_error("Unhandled `symbol_binding`");
            }

            throw std::runtime_error("Invalid `symbol_binding`");
        }
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif