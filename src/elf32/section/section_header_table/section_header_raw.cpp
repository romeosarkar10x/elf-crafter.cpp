#include "elf32/section/section_header_table/section_header_raw.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        section_header_raw::section_header_raw(const std::byte* bytes)
        {
            const section_header_raw& section_header = *reinterpret_cast<const section_header_raw*>(bytes);

            {
                // TODO: Validate all fields
            }

            m_index_section_name = section_header.m_index_section_name;
            m_section_type       = section_header.m_section_type;
            m_address            = section_header.m_address;
            m_file_offset        = section_header.m_file_offset;
            m_size               = section_header.m_size;
            m_link_section_index = section_header.m_link_section_index;
            m_info               = section_header.m_info;
            m_address_alignment  = section_header.m_address_alignment;
            m_entry_size         = section_header.m_entry_size;
        }
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif