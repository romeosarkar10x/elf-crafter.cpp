#include <cmath>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

#include <elf32/elf32.hpp>
#include <elf32/program/program_header_raw.hpp>
#include <elf32/section/relocation/relocation_raw.hpp>
#include <elf32/section/relocation/relocation_with_addends_raw.hpp>
#include <elf32/section/section.hpp>
#include <elf32/section/section_header_raw.hpp>
#include <elf32/section/string_table/string_table.hpp>
#include <elf32/section/symbol_table_entry_raw.hpp>

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

            const size_t section_header_table_file_offset       = m_header.get_section_header_table_file_offset().value;
            const size_t section_header_table_number_of_entries = m_header.get_section_header_table_number_of_entries();
            const size_t section_header_table_entry_size        = m_header.get_section_header_table_entry_size();

            auto buffer = m_file.read(
                section_header_table_number_of_entries * section_header_table_entry_size,
                section_header_table_file_offset
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

            auto get_string_table = [&](size_t index) -> string_table {
                const section_header_raw& string_table_header_raw = section_headers[index];

                auto string_table_bytes =
                    m_file.read(string_table_header_raw.size, string_table_header_raw.file_offset);
                const char* const string_table_section_name = reinterpret_cast<const char*>(
                    string_table_bytes.get() + string_table_header_raw.index_section_name
                );

                return {
                    this,
                    string_table_header_raw.section_type,
                    string_table_section_name,
                    string_table_header_raw.address,
                    string_table_header_raw.address_alignment,
                    string_table_header_raw.size,
                    {},
                    std::move(string_table_bytes)
                };
            };

            const auto section_name_string_table = get_string_table(m_header.get_section_name_string_table_index());

            std::vector<std::pair<symbol*, elf32_word>> skipped_symbols;

            std::vector<section*>    sections;
            std::vector<std::size_t> section_header_raw_indexes_to_section_indexes_jump_table(
                section_header_table_number_of_entries
            );

            std::vector<std::size_t> section_header_raw_indexes_to_symbols_vector_indexes_jump_table(
                section_header_table_number_of_entries
            );

            std::vector<std::vector<std::size_t>> symbol_table_raw_indexes_to_symbols_indexes_jump_table(
                section_header_table_number_of_entries
            );

            std::vector<std::vector<symbol*>> symbols_vector;

            // TODO: handle skipped relocations!

            {
                for (size_t index = 0u; const section_header_raw& section_header : section_headers) {
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
                    {
                        section_header_raw_indexes_to_section_indexes_jump_table[index] = sections.size();

                        sections.push_back(new section(
                            this, section_header.section_type,
                            section_name_string_table.get(section_header.index_section_name), section_header.address,
                            section_header.address_alignment, section_header.size, section_header.flags,
                            m_file.read(section_header.size, section_header.file_offset)

                        ));

                        break;
                    }

                    case enum_section_type::SYMBOL_TABLE:
                    {
                        const auto symbol_table_name_string_table = get_string_table(section_header.link_section_index);

                        const size_t file_offset       = section_header.file_offset;
                        const size_t size              = section_header.size;
                        const size_t entry_size        = section_header.entry_size;
                        const size_t number_of_entries = size / entry_size;

                        section_header_raw_indexes_to_symbols_vector_indexes_jump_table[index] = symbols_vector.size();
                        symbols_vector.emplace_back();
                        symbol_table_raw_indexes_to_symbols_indexes_jump_table[index] = std::vector<std::size_t>(
                            number_of_entries
                        );

                        auto bytes = m_file.read(size, file_offset);

                        const symbol_table_entry_raw* symbol_table = reinterpret_cast<const symbol_table_entry_raw*>(
                            bytes.get()
                        );

                        {
                            size_t                        symbol_table_index = 1u;
                            const symbol_table_entry_raw* begin              = symbol_table + 1u;
                            const symbol_table_entry_raw* end                = symbol_table + number_of_entries;

                            while (begin != end) {
                                symbol* s = nullptr;

                                if (begin->section_header_index == enum_special_section_indexes::ABSOLUTE) {
                                    s = new symbol(
                                        nullptr, symbol_table_name_string_table.get(begin->name_string_table_index),
                                        begin->value, begin->size, begin->info.get_symbol_type(),
                                        begin->info.get_symbol_binding()

                                    );

                                } else if (begin->section_header_index == enum_special_section_indexes::COMMON) {
                                    s = new symbol(
                                        nullptr, symbol_table_name_string_table.get(begin->name_string_table_index),
                                        elf32_word{begin->value}, begin->size, begin->info.get_symbol_type(),
                                        begin->info.get_symbol_binding()
                                    );
                                } else {
                                    s = new symbol(
                                        sections[section_header_raw_indexes_to_section_indexes_jump_table
                                                     [begin->section_header_index]],
                                        symbol_table_name_string_table.get(begin->name_string_table_index),
                                        begin->value, begin->size, begin->info.get_symbol_type(),
                                        begin->info.get_symbol_binding()
                                    );
                                }

                                symbol_table_raw_indexes_to_symbols_indexes_jump_table[index][symbol_table_index] =
                                    symbols_vector.back().size();
                                symbols_vector.back().push_back(s);

                                if (enum_special_section_indexes::RESERVED_LOW <= begin->section_header_index &&
                                    begin->section_header_index <= enum_special_section_indexes::RESERVED_HIGH) {
                                    m_symbols.push_back(s);
                                } else {
                                    if (begin->section_header_index > index) {
                                        skipped_symbols.emplace_back(s, begin->section_header_index);
                                    } else {
                                        sections[section_header_raw_indexes_to_section_indexes_jump_table
                                                     [begin->section_header_index]]
                                            ->add_symbol(s);
                                        m_symbols.push_back(s);

                                        section_header_raw_indexes_to_section_indexes_jump_table[index] = sections.size(
                                                                                                          ) -
                                                                                                          1u;
                                    }
                                }

                                begin++;
                                symbol_table_index++;
                            }
                        }

                        break;
                    }

                    case enum_section_type::STRING_TABLE:
                        break;

                    case enum_section_type::RELOCATION:
                    case enum_section_type::RELOCATION_WITH_ADDENDS:
                    {
                        const size_t file_offset       = section_header.file_offset;
                        const size_t size              = section_header.size;
                        const size_t entry_size        = section_header.entry_size;
                        const size_t number_of_entries = size / entry_size;

                        auto     symbol_table_section_header_index = section_header.link_section_index;
                        auto     relocation_section_header_index   = section_header.info;
                        section* relocation_section                = sections
                            [section_header_raw_indexes_to_section_indexes_jump_table[relocation_section_header_index]];
                        auto& symbols = symbols_vector[section_header_raw_indexes_to_symbols_vector_indexes_jump_table
                                                           [symbol_table_section_header_index]];

                        auto bytes = m_file.read(size, file_offset);

                        if (section_header.section_type == enum_section_type::RELOCATION) {
                            const relocation_raw* table = reinterpret_cast<const relocation_raw*>(bytes.get());

                            {
                                const relocation_raw* begin = table;
                                const relocation_raw* end   = table + number_of_entries;

                                while (begin != end) {
                                    auto symbol_table_index = begin->info.symbol_table_index;

                                    relocation* r = new relocation(
                                        relocation_section,
                                        symbols[symbol_table_raw_indexes_to_symbols_indexes_jump_table
                                                    [symbol_table_section_header_index][symbol_table_index]],
                                        begin->offset, 0, begin->info.type
                                    );

                                    m_relocations.push_back(r);

                                    begin++;
                                }
                            }
                        } else {
                            const relocation_with_addends_raw* table =
                                reinterpret_cast<const relocation_with_addends_raw*>(bytes.get());

                            {
                                const relocation_with_addends_raw* begin = table;
                                const relocation_with_addends_raw* end   = table + number_of_entries;

                                while (begin != end) {
                                    begin++;

                                    relocation* r = new relocation(
                                        sections[section_header_raw_indexes_to_section_indexes_jump_table[section_header
                                                                                                              .info]],
                                        symbols_vector[section_header_raw_indexes_to_symbols_vector_indexes_jump_table
                                                           [section_header.link_section_index]]
                                                      [begin->info.symbol_table_index],
                                        begin->offset, begin->addend, begin->info.type
                                    );

                                    m_relocations.push_back(r);
                                }
                            }
                        }

                        break;
                    }

                    case enum_section_type::HASH:
                        break;

                    case enum_section_type::DYNAMIC:
                        break;

                    case enum_section_type::NOTE:
                        break;

                    case enum_section_type::NO_BITS:
                        break;

                    case enum_section_type::LIB:
                        break;

                    case enum_section_type::DYNAMIC_SYMBOL:
                        break;

                    default:
                        throw std::runtime_error("Invalid `section_type`");
                    }

                    index++;
                }
            }

            {
                // Reconciliate skipped symbols
                for (auto&& [s, index] : skipped_symbols) {
                    sections[section_header_raw_indexes_to_section_indexes_jump_table[index]]->add_symbol(s);
                    m_symbols.push_back(s);
                }
            }

            {
                // Parse program-header
                size_t number_of_entries = m_header.get_program_header_table_number_of_entries();
                size_t entry_size        = m_header.get_program_header_table_entry_size();
                size_t file_offset       = m_header.get_program_header_table_file_offset();

                const auto bytes = m_file.read(entry_size * number_of_entries, file_offset);

                const program_header_raw* program_header_table = reinterpret_cast<const program_header_raw*>(bytes.get()
                );

                {
                    const program_header_raw* begin = program_header_table;
                    const program_header_raw* end   = begin + number_of_entries;

                    while (begin != end) {
                        std::cout << std::hex << static_cast<uint32_t>(begin->segment_type) << std::endl;
                        std::cout << "PROGRAM_HEADER_RAW" << (*begin | lonifier() | stringifier()) << std::endl;
                        begin++;
                    }
                }
            }

            for (auto&& [skipped_symbol, index] : skipped_symbols) {
                std::cout << (*skipped_symbol | lonifier() | stringifier()) << std::endl;
            }

            for (auto symbol : m_symbols) {
                std::cout << (*symbol | lonifier() | stringifier()) << std::endl;
            }

            std::cout << "Relocations: " << std::endl;
            for (auto relocation : m_relocations) {
                std::cout << (*relocation | lonifier() | stringifier()) << std::endl;
            }
            std::cout << "### ### ###" << std::endl;

            for (const section* s : sections) {
                std::cout << (*s | lonifier() | stringifier()) << std::endl;
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
