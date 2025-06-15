#include <elf32/section/section.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        section::section() {}
        section::section(
            elf32* elf, const enum_section_type type, const char* const name, const elf32_address address,
            const elf32_word address_alignment, const elf32_word size, std::unique_ptr<std::byte> bytes
        )
            : m_elf{elf},
              m_type{type},
              m_name{name},
              m_address{address},
              m_address_alignment{address_alignment},
              m_size{size},
              m_bytes{std::move(bytes)}
        {}

        void section::add_symbol(symbol* s)
        {
            m_symbols.push_back(s);
        }

        const lon_type* operator|(const section& s, const lonifier& l)
        {
            lon_object* lo = new lon_object;

            lo->set_key("Pointer", &s | l);
            lo->set_key("Name", new lon_string(s.m_name));
            lo->set_key("Type", s.m_type | l);
            lo->set_key("Address", s.m_address | l);
            lo->set_key("Address alignment", s.m_address_alignment | l);
            lo->set_key("Size", s.m_size | l);
            lo->set_key("Bytes", new lon_bytes(s.m_bytes.get(), s.m_size));

            return lo;
        }
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif