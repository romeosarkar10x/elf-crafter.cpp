#ifndef ELF_CRAFTER_ELF32_HEADER_HPP
#define ELF_CRAFTER_ELF32_HEADER_HPP

#include <config.hpp>

#include <utility/file.hpp>

#include "header_raw.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        struct header
        {
            header();
            header(file& f);

            elf32_offset get_program_header_table_offset() const;
            elf32_half   get_program_header_number_of_entries() const;
            elf32_half   get_program_header_table_entry_size() const;

            elf32_offset get_section_header_table_offset() const;
            elf32_half   get_section_header_table_number_of_entries() const;
            elf32_half   get_section_header_table_entry_size() const;

            elf32_half get_section_name_string_table_index() const;

            friend const lon_type* operator|(const header& header, const lonifier& l);

        private:
            header_raw* m_header_raw = nullptr;
        };
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif

#endif