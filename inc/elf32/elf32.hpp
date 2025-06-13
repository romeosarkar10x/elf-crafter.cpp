#ifndef ELF_CRAFTER_ELF_HPP
#define ELF_CRAFTER_ELF_HPP

#include <unistd.h>
#include <vector>

#include "elf32/header/header_raw.hpp"
#include "elf32/section/section_header_table/section_header_table.hpp"
#include "elf32/section/string_table/string_table.hpp"
#include "elf32/section/symbol_table/symbol_table.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        struct elf32
        {
            elf32(const char* pathname, bool write = false);

            void open_file(const char* pathname, bool write = false);
            void close_file();

            void write_file();
            void write_file(const char* pathname);

            const section_header_table& get_section_header_table() const;
            section_header_table&       get_section_header_table();

            const section& get_section(elf32_offset index) const;

            const std::vector<symbol_table> get_symbol_table() const;
            symbol_table                    get_symbol_table();

            const string_table get_string_table() const;
            string_table       get_string_table();

        private:
            int m_file_descriptor{-1};

            header_raw m_header;

            section_header_table m_section_header_table;

            symbol_table m_symbol_table;
            string_table m_string_table;
        };
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
} // namespace elf_crafter
#endif

#endif