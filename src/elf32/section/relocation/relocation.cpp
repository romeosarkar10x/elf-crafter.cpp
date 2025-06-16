#include <elf32/section/relocation/relocation.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        relocation::relocation(
            section* section, symbol* symbol, elf32_address offset, elf32_signed_word addend, enum_relocation_type type
        )

            : m_section{section}, m_symbol{symbol}, m_offset{offset}, m_addend{addend}, m_type{type}
        {}

        const lon_type* operator|(const relocation& r, const lonifier& l)
        {
            lon_object* lo = new lon_object;

            lo->set_key("Section", r.m_section | l);
            lo->set_key("Symbol", *r.m_symbol | l);
            lo->set_key("Offset", r.m_offset | l);
            lo->set_key("Addend", r.m_addend | l);

            return lo;
        }
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif
