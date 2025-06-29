#ifndef ELF_CRAFTER_ELF_HPP
#define ELF_CRAFTER_ELF_HPP

#include <unistd.h>
#include <vector>

#include <elf32/header/header.hpp>
#include <elf32/section/relocation/relocation.hpp>
#include <elf32/section/string_table/string_table.hpp>
#include <elf32/section/symbol_table/symbol_table.hpp>
#include <utility/file.hpp>

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

            /*
            const std::vector<section>& get_sections(enum_section_type section_type);
            const section&              get_section(enum_section_type, std::size_t index) const;
            */

            void create_new_section();
            void delete_section(enum_section_type section_type, std::size_t index);

        private:
            file                                               m_file;
            header                                             m_header;
            std::map<enum_section_type, std::vector<section*>> m_sections;
            std::vector<symbol*>                               m_symbols;
            std::vector<relocation*>                           m_relocations;
        };
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
} // namespace elf_crafter
#endif

#endif