
#include <iostream>

#include <utility/file.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    file::file() {}

    file::file(const char* const pathname, const bool write)
        : m_file_descriptor{::open(pathname, write ? O_WRONLY | O_CREAT : O_RDONLY)}
    {
        m_check_open();
    }

    file::~file()
    {
        if (m_file_descriptor == -1) {
            return;
        }

        file::close();
    }

    void file::open(const char* const pathname, const bool write)
    {
        m_file_descriptor = ::open(pathname, write ? O_WRONLY | O_CREAT : O_RDONLY);
        m_check_open();
    }

    void file::m_check_open() const
    {
        if (m_file_descriptor == -1) {
            // TODO: Handle all errors!
            throw std::runtime_error("error opening file!");
        }
    }

    void file::m_check_offset(const off_t offset) const
    {
        if (offset == -1) {
            // TODO: Handle all errors!

            throw std::runtime_error("error seeking file!");
        }
    }

    void file::close()
    {
        m_check_open();

        int ret = ::close(m_file_descriptor);

        if (ret == -1) {
            throw std::runtime_error("failed to close file!");
        }
    }

    std::size_t file::get_offset() const
    {
        m_check_open();

        off_t offset = lseek(m_file_descriptor, 0, SEEK_CUR);
        m_check_offset(offset);

        return static_cast<std::size_t>(offset);
    }

    void file::set_offset(const std::size_t offset)
    {
        m_check_open();

        off_t ret = lseek(m_file_descriptor, static_cast<off_t>(offset), SEEK_SET);
        m_check_offset(ret);
    }

    std::unique_ptr<std::byte> file::read(const std::size_t number_of_bytes)
    {
        m_check_open();

        std::byte* buffer = new std::byte[number_of_bytes];

        size_t number_of_bytes_to_read = number_of_bytes;
        size_t number_of_bytes_read    = 0u;

        while (number_of_bytes_to_read) {
            ::ssize_t number_of_bytes_currently_read =
                ::read(m_file_descriptor, buffer + number_of_bytes_read, number_of_bytes_to_read);

            if (number_of_bytes_currently_read == -1) {
                // TODO: Handle errors
                throw std::runtime_error("Error while reading file!");
            } else if (number_of_bytes_currently_read == 0) {
                throw std::runtime_error("Unexpected end of file");
            }

            number_of_bytes_to_read -= static_cast<std::size_t>(number_of_bytes_currently_read);
            number_of_bytes_read += static_cast<std::size_t>(number_of_bytes_currently_read);
        }

        return std::unique_ptr<std::byte>(buffer);
    }

    std::unique_ptr<std::byte> file::read(const std::size_t number_of_bytes, const std::size_t file_offset)
    {
        file::set_offset(file_offset);
        return file::read(number_of_bytes);
    }

    void file::write(const std::byte* const bytes, const std::size_t number_of_bytes)
    {
        m_check_open();

        ::size_t number_of_bytes_to_write = number_of_bytes;
        ::size_t number_of_bytes_written  = 0u;

        while (number_of_bytes_to_write) {
            ::ssize_t number_of_bytes_currently_written =
                ::write(m_file_descriptor, bytes + number_of_bytes_written, number_of_bytes_to_write);

            if (number_of_bytes_currently_written == -1) {
                // TODO: Handle errors
                throw std::runtime_error("Failed to write to file");
            }
        }
    }

    void file::write(const std::byte* const bytes, const std::size_t number_of_bytes, const std::size_t file_offset)
    {
        file::set_offset(file_offset);
        file::write(bytes, number_of_bytes);
    }

#ifdef PROJECT_NAMESPACE
}
#endif