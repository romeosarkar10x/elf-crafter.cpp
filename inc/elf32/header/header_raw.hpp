#ifndef ELF_HEADER_HPP
#define ELF_HEADER_HPP

#include <config.hpp>
#include <memory>

#include <elf32/header/identification_raw.hpp>
#include <elf32/type.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        struct header_raw
        {
            enum struct enum_object_type : elf32_half::type
            {
                NONE,
                RELOCATABLE,
                EXECUTABLE,
                SHARED_OBJECT,
                CORE,
                LO_PROCESSOR_SPECIFIC,
                HI_PROCESSOR_SPECIFIC,
            };

            friend const lon_type* operator|(enum_object_type object_type, const lonifier& l);

            enum struct enum_machine_type : elf32_half::type
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

            friend const lon_type* operator|(enum_machine_type machine_type, const lonifier& l);

            header_raw();
            header_raw(const std::byte* bytes);

            identification_raw identification;

            enum_object_type  object_type;
            enum_machine_type machine;
            enum_elf_version  version;

            elf32_address entry_point;

            elf32_offset program_header_table_file_offset;
            elf32_offset section_header_table_file_offset;

            elf32_word flags;

            elf32_half elf_header_size;

            elf32_half program_header_table_entry_size;
            elf32_half program_header_number_of_entries;

            elf32_half section_header_table_entry_size;
            elf32_half section_header_table_number_of_entries;

            elf32_half section_name_string_table_index;
        };
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
} // namespace PROJECT_NAMESPACE
#endif

#endif