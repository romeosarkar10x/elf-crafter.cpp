#include "elf32/elf32.hpp"

#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        elf32::elf32(const char* const pathname, const bool write) : m_file{pathname, write}, m_header{m_file}
        {
            auto& section_headers = section_header_table(
                                        m_file, m_header.get_section_header_offset(),
                                        m_header.get_section_header_number_of_entries()
            )
                                        .get_section_headers();

            std::cout << (m_header | lonifier() | stringifier()) << std::endl;
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
