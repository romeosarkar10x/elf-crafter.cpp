/*
#ifndef ELF_CRAFTER_SECTION_HEADER_TABLE_HPP
#define ELF_CRAFTER_SECTION_HEADER_TABLE_HPP

#include <config.hpp>

#include <elf32/header/identification_raw.hpp>
#include <utility/file.hpp>

#include "section_header_raw.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        struct section_header_table
        {
            section_header_table(file& f, elf32_offset section_header_table_offset, elf32_half number_of_entries);
            const std::vector<section_header_raw>& get_section_headers() const;

        private:
            std::vector<section_header_raw> m_section_headers;
        };
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif

#endif
*/