#ifndef ELF_CRAFTER_UTILITY_FILE_HPP
#define ELF_CRAFTER_UTILITY_FILE_HPP

#include <config.hpp>
#include <cstddef>
#include <fcntl.h>
#include <memory>
#include <unistd.h>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    struct file
    {
        file();
        file(const char* pathname, bool write = false);
        ~file();

        void open(const char* pathname, bool write = false);
        void close();

        std::size_t get_offset() const;
        void        set_offset(std::size_t offset);

        std::unique_ptr<std::byte> read(std::size_t number_of_bytes);
        std::unique_ptr<std::byte> read(std::size_t number_of_bytes, std::size_t file_offset);

        void write(const std::byte* bytes, std::size_t number_of_bytes);
        void write(const std::byte* bytes, std::size_t number_of_bytes, std::size_t file_offset);

    private:
        int m_file_descriptor = -1;

        void m_check_open() const;
        void m_check_offset(off_t offset) const;
        void m_check_memory(const void* pointer) const;
    };

#ifdef PROJECT_NAMESPACE
}
#endif

#endif