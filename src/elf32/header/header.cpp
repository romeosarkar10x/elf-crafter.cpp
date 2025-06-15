#include <elf32/header/header.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        header::header() {};

        header::header(file& f)
        {
            std::unique_ptr<std::byte> bytes = f.read(sizeof(header_raw), 0u);
            m_header_raw                     = new header_raw(bytes.get());
        }

        elf32_offset header::get_program_header_table_file_offset() const
        {
            return m_header_raw->program_header_table_file_offset;
        }

        elf32_half header::get_program_header_number_of_entries() const
        {
            return m_header_raw->program_header_number_of_entries;
        }

        elf32_half header::get_program_header_table_entry_size() const
        {
            return m_header_raw->program_header_table_entry_size;
        }

        elf32_offset header::get_section_header_table_file_offset() const
        {
            return m_header_raw->section_header_table_file_offset;
        }

        elf32_half header::get_section_header_table_number_of_entries() const
        {
            return m_header_raw->section_header_table_number_of_entries;
        }

        elf32_half header::get_section_header_table_entry_size() const
        {
            return m_header_raw->section_header_table_entry_size;
        }

        elf32_half header::get_section_name_string_table_index() const
        {
            return m_header_raw->section_name_string_table_index;
        }

        const lon_type* operator|(const header& header, const lonifier& l)
        {
            lon_object* lo = new lon_object;

            lo->set_key("Identification", header.m_header_raw->identification | l);
            lo->set_key("Object type", header.m_header_raw->object_type | l);
            lo->set_key("Machine", header.m_header_raw->machine | l);

            lo->set_key("Version", header.m_header_raw->version | l);
            lo->set_key("Entry point", header.m_header_raw->entry_point | l);
            lo->set_key("Program-header offset", header.m_header_raw->program_header_table_file_offset | l);
            lo->set_key("Section-header offset", header.m_header_raw->section_header_table_file_offset | l);

            // TODO: implement elf-header flags
            // lo->set_key("Flags: ")

            lo->set_key("ELF header size", (header.m_header_raw->elf_header_size.value | l));

            lo->set_key("Program-header entry size", header.m_header_raw->program_header_table_entry_size.value | l);
            lo->set_key(
                "Program-header number of entries", header.m_header_raw->program_header_number_of_entries.value | l
            );

            lo->set_key("Section-header entry size", header.m_header_raw->section_header_table_entry_size.value | l);
            lo->set_key(
                "Section-header number of entries",
                header.m_header_raw->section_header_table_number_of_entries.value | l
            );

            lo->set_key(
                "Section-name string-table index",
                std::to_string(header.m_header_raw->section_name_string_table_index.value) | l
            );

            return lo;
        }
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif