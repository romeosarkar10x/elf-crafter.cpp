#include <climits>
#include <stdexcept>
#include <unistd.h>

#include "elf32/header/header_raw.hpp"

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

            size_t num_of_bytes_read    = 0;
            size_t num_of_bytes_to_read = sizeof(header_raw);

            while (num_of_bytes_to_read) {
                num_of_bytes_read +=
                    read(file_descriptor, buffer + num_of_bytes_read, num_of_bytes_to_read);

                if (num_of_bytes_read == 0) {
                    if (errno != EAGAIN) {
                        throw std::runtime_error("unexpected end of file!");
                    }
                }
            }
        }
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
}
#endif