#include "elf32/section/section_header_table/section_header_table.hpp"

#include <stdexcept>
#include <unistd.h>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        section_header_table::section_header_table(
            file& f, elf32_offset section_header_offset, elf32_half number_of_entries
        )
        {
            const size_t               size  = number_of_entries * sizeof(section_header_raw);
            std::unique_ptr<std::byte> bytes = f.read(size);

            {
                const section_header_raw* begin = reinterpret_cast<section_header_raw*>(bytes.get());
                const section_header_raw* end   = reinterpret_cast<section_header_raw*>(bytes.get() + size);

                while (begin != end) {
                    m_section_headers.emplace_back(reinterpret_cast<const std::byte*>(begin));
                    begin++;
                }
            }
        }

        const std::vector<section_header_raw>& section_header_table::get_section_headers() const
        {
            return m_section_headers;
        }
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif