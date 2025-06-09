#ifndef ELF_HEADER_HPP
#define ELF_HEADER_HPP

#include "elf_types.hpp"

namespace elf_crafter
{
    struct elf32_header
    {
    private:
        elf32_unsigned_char m_identification[16u];

        enum struct enum_object_type : elf32_half
        {
            NONE,
            RELOCATABLE,
            EXECUTABLE,
            SHARED_OBJECT,
            CORE,
            LO_PROCESSOR_SPECIFIC,
            HI_PROCESSOR_SPECIFIC,
        };

        enum_object_type m_object_type;

        enum struct enum_machine_type : elf32_half
        {
            NONE,
            M32,
            SPARC,
            INTEL_386,
            MOTOROLA_68K,
            MOTOROLA_88K,
            INTEL_80860 = 7u,
            MIPS_RS3000_BIG_ENDIAN,
            MIPS_RS4000_BIG_ENDIAN = 10u,
            RESERVED_11,
            RESERVED_12,
            RESERVED_13,
            RESERVED_14,
            RESERVED_15,
            RESERVED_16,
        };

        elf32_half m_machine;

        elf32_word m_version;

        elf32_address m_entry_point;
        elf32_offset  m_program_header_offset;
        elf32_offset  m_section_header_offset;

        elf32_word m_flags;

        elf32_half m_elf_header_size;
        elf32_half m_program_header_entry_size;
        elf32_half m_program_header_number_of_entries;

        elf32_half m_section_header_entry_size;
        elf32_half m_section_header_number_of_entries;

        elf32_half m_section_name_string_table_index;
    };

} // namespace elf_crafter

#endif