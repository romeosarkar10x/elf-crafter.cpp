#ifndef SECTION_HEADER_HPP
#define SECTION_HEADER_HPP

#include "elf_types.hpp"

namespace elf_crafter
{
    struct section_header
    {
        enum enum_section_type : elf32_word
        {
            NULL,
            PROGRAM_BITS,
            SYMBOL,
            STRING,
            RELOCATION_ADDENDS,
            HASH,
            DYNAMIC,
            NOTE,
            NO_BITS,
            RELOCATION,
            LIB,
            DYNAMIC_SYMBOL,

            LO_PROC = 0x70000000,
            HI_PROC = 0x7fffffff,

            LO_USER = 0x80000000,
            HI_USER = 0xffffffff,
        };

        enum enum_section_attributes_flags : elf32_word
        {
            WRITEABLE = 1u,
            ALLOC,
            EXECUTABLE,
            PROCESSOR_SPECIFIC_SEMANTICS_MASK,
        };

        const char* get_section_name() const;
        void set_section_name();

        enum_section_type get_section_type() const;
        void set_section_type(enum_section_type section_type);

    private:
        elf32_word m_index_section_name;

        enum_section_type m_section_type;

        elf32_word m_flags;
        elf32_address m_address;
        elf32_offset m_offset;

        elf32_word m_size;
        elf32_word m_link;
        elf32_word m_info;
        elf32_word m_address_alignment;
        elf32_word m_entry_size;
    };

    constexpr section_header section_header_undef = {

    };
} // namespace elf_crafter

#endif