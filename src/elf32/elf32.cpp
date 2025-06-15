#include <cmath>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

#include <elf32/elf32.hpp>
#include <elf32/section/section_header_raw.hpp>
#include <elf32/section/string_table/string_table.hpp>

#include "elf32/section/type.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        elf32::elf32(const char* const pathname, const bool write) : m_file{pathname, write}, m_header{m_file}
        {
            std::cout << (m_header | lonifier() | stringifier()) << std::endl;

            const size_t section_header_table_offset            = m_header.get_section_header_table_offset().value;
            const size_t section_header_table_number_of_entries = m_header.get_section_header_table_number_of_entries();
            const size_t section_header_table_entry_size        = m_header.get_section_header_table_entry_size();

            auto buffer = m_file.read(
                section_header_table_number_of_entries * section_header_table_entry_size, section_header_table_offset
            );

            const section_header_raw*       section_header_table = reinterpret_cast<section_header_raw*>(buffer.get());
            std::vector<section_header_raw> section_headers;

            {
                const section_header_raw* begin = section_header_table;
                const section_header_raw* end   = section_header_table + section_header_table_number_of_entries;

                while (begin != end) {
                    section_headers.emplace_back(reinterpret_cast<const std::byte*>(begin));
                    begin++;
                }
            }

            const section_header_raw& string_table_header_raw =
                section_headers[m_header.get_section_name_string_table_index()];

            auto string_table_bytes = m_file.read(string_table_header_raw.size, string_table_header_raw.file_offset);
            const char* const string_table_section_name = reinterpret_cast<const char*>(
                string_table_bytes.get() + string_table_header_raw.index_section_name
            );

            const string_table str_table(
                this, string_table_header_raw.section_type, string_table_section_name, string_table_header_raw.address,
                string_table_header_raw.address_alignment, string_table_header_raw.size, std::move(string_table_bytes)
            );

            std::vector<section> sections;

            {
                for (const section_header_raw& section_header : section_headers) {
                    if (&section_header == &string_table_header_raw) {
                        continue;
                    }

                    /*
                    std::cout << "#### #### #### ####" << std::endl;
                    std::cout << "section_type: " << (section_header.section_type | lonifier() | stringifier())
                              << std::endl;
                    std::cout << "address:" << (section_header.address | lonifier() | stringifier()) << std::endl;
                    std::cout << "file_offset: " << (section_header.file_offset | lonifier() | stringifier())
                              << std::endl;
                    std::cout << "flags: " << (section_header.flags | lonifier() | stringifier()) << std::endl;
                    std::cout << "link_section_index: "
                              << (section_header.link_section_index | lonifier() | stringifier()) << std::endl;
                    std::cout << "size: " << (section_header.size | lonifier() | stringifier()) << std::endl;

                    std::cout << "---- ---- ---- ----" << std::endl;
                    */

                    auto bytes = m_file.read(section_header.size, section_header.file_offset);

                    switch (section_header.section_type) {
                    case enum_section_type::NULL_TYPE:
                        break;

                    case enum_section_type::PROGRAM_BITS:
                        sections.emplace_back(
                            this, section_header.section_type, str_table.get(section_header.index_section_name),
                            section_header.address, section_header.address_alignment, section_header.size,
                            m_file.read(section_header.size, section_header.file_offset)
                        );

                        std::cout << (sections.back() | lonifier() | stringifier()) << std::endl;

                    case enum_section_type::SYMBOL_TABLE:

                        break;

                    case enum_section_type::STRING_TABLE:
                        break;

                    case enum_section_type::RELOCATION_WITH_ADDENDS:
                        break;

                    case enum_section_type::HASH:
                        break;

                    case enum_section_type::DYNAMIC:
                        break;

                    case enum_section_type::NOTE:
                        break;

                    case enum_section_type::NO_BITS:
                        break;

                    case enum_section_type::RELOCATION:
                        break;

                    case enum_section_type::LIB:
                        break;

                    case enum_section_type::DYNAMIC_SYMBOL:
                        break;

                    default:
                        throw std::runtime_error("Invalid `section_type`");
                    }
                    sections.emplace_back();
                }
            }
        }

        void elf32::open_file(const char* const pathname, const bool write)
        {
            m_file.open(pathname, write);
        }

        void elf32::close_file()
        {
            m_file.close();
        }

        void elf32::write_file()
        {
            throw std::runtime_error("Not implemented!");
        }

        void elf32::write_file(const char* const filename)
        {
            throw std::runtime_error("Not implemented!!");
        }
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif
