#include "elf32/elf32.hpp"

#include <fcntl.h>
#include <stdexcept>
#include <unistd.h>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        elf32::elf32(const char* const pathname, const bool write)
            : m_file_descriptor{open(pathname, write ? O_WRONLY | O_CREAT : O_RDONLY)},
              m_header{m_file_descriptor}
        {}

        void elf32::open_file(const char* const pathname, const bool write)
        {
            if (write) {
                m_file_descriptor = open(pathname, O_WRONLY | O_CREAT);

            } else {
                m_file_descriptor = open(pathname, O_RDONLY);
            }

            if (m_file_descriptor == -1) {
                throw std::runtime_error("cannot open file!");
            }
        }

        void elf32::close_file() {}

        void elf32::write_file() {}

        void elf32::write_file(const char* const filename) {}
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif
