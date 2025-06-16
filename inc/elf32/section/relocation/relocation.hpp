#pragma once

#include <config.hpp>

#include <elf32/forward_declaration.hpp>
#include <elf32/section/symbol.hpp>
#include <elf32/type.hpp>

#include "relocation_info_raw.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        struct relocation
        {
            relocation(
                section* section, symbol* symbol, elf32_address offset, elf32_signed_word addend,
                enum_relocation_type type
            );

            friend const lon_type* operator|(const relocation& r, const lonifier& l);

        private:
            section*             m_section;
            symbol*              m_symbol;
            elf32_address        m_offset;
            elf32_signed_word    m_addend = 0;
            enum_relocation_type m_type;
        };
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif