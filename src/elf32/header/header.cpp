#include <climits>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

#include "elf32/header/header_raw.hpp"
#include "elf32/header/identification_raw.hpp"
#include "utility/stringifier.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        header_raw::header_raw(int file_descriptor)
        {
            if (file_descriptor == -1) {
                throw std::runtime_error("file_descriptor == -1");
            }

            off_t pos = lseek(file_descriptor, 0, SEEK_CUR);

            if (pos == -1) {
                // TODO: Handle errors.
                if (errno == EBADF) {
                } else if (errno == EINVAL) {
                } else if (errno == ENXIO) {
                } else if (errno == EOVERFLOW) {
                } else if (errno == ESPIPE) {
                }
            }

            {
                off_t ret = lseek(file_descriptor, 0, SEEK_SET);

                if (ret == -1) {
                    // TODO: Handle errors.
                    if (errno == EBADF) {
                    } else if (errno == EINVAL) {
                    } else if (errno == ENXIO) {
                    } else if (errno == EOVERFLOW) {
                    } else if (errno == ESPIPE) {
                    }
                }
            }

            std::byte* buffer = reinterpret_cast<std::byte*>(this);

            size_t number_of_bytes_read    = 0;
            size_t number_of_bytes_to_read = sizeof(header_raw);

            while (number_of_bytes_to_read) {
                ssize_t current_number_of_bytes_read =
                    read(file_descriptor, buffer + number_of_bytes_read, number_of_bytes_to_read);

                number_of_bytes_read += current_number_of_bytes_read;
                number_of_bytes_to_read -= current_number_of_bytes_read;

                if (number_of_bytes_read == 0) {
                    if (errno != EAGAIN) {
                        throw std::runtime_error("unexpected end of file!");
                    }
                }
            }

            new (&m_identification) identification_raw(buffer);

            std::cout << (m_identification | lonifier() | stringifier()) << std::endl;

            // TODO: Validate each field.
            {
                // Validate `machine`
            }

            {
                // Validate `version`
            }

            {
                // Validate `entry_point`
            }

            {
                // Validate `program_header_offset`
            }

            {
                // Validate `section_header_offset`
            }

            {
                // Validate `flags`
            }

            {
                // Validate `elf_header_size`
            }

            {
                // Validate `program_header_entry_size`
            }

            {
                // Validate `program_header_number_of_entries`
            }

            {
                // Validate `section_header_entry_size`
            }

            {
                // Validate `section_header_number_of_entries`
            }

            {
                // Validate `section_name_string_table_index`
            }
        }

    } // namespace elf32
#ifdef PROJECT_NAMESPACE
}
#endif