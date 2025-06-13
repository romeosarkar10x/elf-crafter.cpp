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
            int file_descriptor, elf32_offset section_header_offset, elf32_half number_of_entries
        )
        {
            const off_t last_offset = lseek(file_descriptor, 0, SEEK_CUR);

            if (last_offset == -1) {
                // TODO: Handle errors properly
                if (errno == EBADF) {
                    throw std::runtime_error("file_descriptor is not an open file descriptor");
                } else if (errno == EINVAL) {
                    throw std::runtime_error("whence is not valid, or the resulting file offset would be negative or "
                                             "beyond the end of a seekable device");
                }

                throw std::runtime_error("failed to get last_offset");
            }

            {
                const off_t offset = lseek(file_descriptor, static_cast<off_t>(section_header_offset.value), SEEK_SET);

                if (offset == -1) {
                    // TODO: Handle errors properly
                    throw std::runtime_error("failed to seek to section_header_offset");
                }
            }

            const size_t buffer_size             = number_of_entries.value * sizeof(section_header_raw);
            size_t       number_of_bytes_to_read = buffer_size;
            std::byte*   buffer                  = new std::byte[buffer_size];

            {
                // Read from file
                size_t number_of_bytes_read = 0;

                while (number_of_bytes_to_read) {
                    ssize_t current_number_of_bytes_read =
                        read(file_descriptor, buffer + number_of_bytes_read, number_of_bytes_to_read);

                    if (current_number_of_bytes_read == 0) {
                        throw std::runtime_error("unexpected end of file!");
                    } else if (current_number_of_bytes_read == -1) {
                        if (errno != EAGAIN) {
                            // TODO: Handle errors
                            throw std::runtime_error(
                                "an error occurred while reading bytes, at section_header_table.cpp"
                            );
                        }
                    }

                    number_of_bytes_read += current_number_of_bytes_read;
                    number_of_bytes_to_read -= current_number_of_bytes_read;
                }
            }

            {
                const section_header_raw* begin = reinterpret_cast<section_header_raw*>(buffer);
                const section_header_raw* end   = reinterpret_cast<section_header_raw*>(buffer + buffer_size);

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