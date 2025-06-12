#ifndef ELF_HEADER_HPP
#define ELF_HEADER_HPP

#include "config.hpp"
#include "elf32/header/identification_raw.hpp"
#include "elf32/types.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        struct header_raw
        {
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

            header_raw();
            header_raw(int file_descriptor);

        private:
            identification_raw m_identification;

            enum_object_type m_object_type;
            elf32_half       m_machine;
            elf32_word       m_version;

            elf32_address m_entry_point;

            elf32_offset m_program_header_offset;
            elf32_offset m_section_header_offset;

            elf32_word m_flags;

            elf32_half m_elf_header_size;
            elf32_half m_program_header_entry_size;
            elf32_half m_program_header_number_of_entries;

            elf32_half m_section_header_entry_size;
            elf32_half m_section_header_number_of_entries;

            elf32_half m_section_name_string_table_index;
        };
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
} // namespace PROJECT_NAMESPACE
#endif

#endif