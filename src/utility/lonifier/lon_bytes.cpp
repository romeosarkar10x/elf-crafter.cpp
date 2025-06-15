#include <iomanip>
#include <iostream>
#include <sstream>

#include <utility/lonifier/lon_bytes.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    lon_bytes::lon_bytes(const std::byte* const bytes, const std::size_t size)
        : m_data{new std::byte[size]}, m_size{size}
    {
        std::copy(bytes, bytes + size, m_data.get());
    }

    lon_type::enum_lon_type lon_bytes::get_type() const
    {
        return enum_lon_type::BYTES;
    }

    const std::string operator|(const lon_bytes& lb, const stringifier& s)
    {
        std::ostringstream oss;
        oss << "<" << std::endl;

        const std::size_t size                    = lb.m_size;
        const std::size_t number_of_bytes_per_row = 16u;
        const std::size_t number_of_rows          = (size + number_of_bytes_per_row - 1u) / number_of_bytes_per_row;

        std::size_t offset       = 0u;
        std::size_t offset_width = 0u;

        {
            std::size_t n = size;

            while (n) {
                offset_width++;
                n >>= 4u;
            }

            offset_width = std::max<std::size_t>(offset_width, 1u);
        }

        s.increment_depth();

        {
            // Header
            for (uint16_t depth = 0u; depth < s.get_depth(); depth++) {
                oss << s.get_box_character(0u) << std::string(s.get_lon_indent_width() - 1u, ' '); // Indent
            }

            oss << s.get_box_character(2u);

            for (std::size_t i = 0; i < offset_width; i++) {
                oss << s.get_box_character(1u);
            }

            oss << s.get_box_character(6u);

            for (std::size_t i = 0; i < number_of_bytes_per_row * 3u - 1u; i++) {
                oss << s.get_box_character(1u);
            }

            oss << s.get_box_character(6u);

            for (std::size_t i = 0; i < number_of_bytes_per_row; i++) {
                oss << s.get_box_character(1u);
            }

            oss << s.get_box_character(3u) << std::endl;
        }

        for (size_t row = 0u; row < number_of_rows; row++, offset += number_of_bytes_per_row) {
            for (uint16_t depth = 0u; depth < s.get_depth(); depth++) {
                oss << s.get_box_character(0u) << std::string(s.get_lon_indent_width() - 1u, ' '); // Indent
            }

            oss << s.get_box_character(0u) << std::hex << std::setw(offset_width) << std::setfill('0') << offset
                << s.get_box_character(0u);

            for (std::size_t i = 0u; i < number_of_bytes_per_row; i++) {
                const size_t current_offset = offset + i;

                if (current_offset >= size) {
                    oss << "xx";
                } else {
                    oss << std::setw(2u) << std::hex << static_cast<uint32_t>(lb.m_data.get()[current_offset]);
                }

                if (i != number_of_bytes_per_row - 1u) {
                    oss << " ";
                } else {
                    oss << s.get_box_character(0u);
                }
            }

            for (std::size_t i = 0; i < number_of_bytes_per_row; i++) {
                const size_t current_offset = offset + i;

                if (current_offset >= size) {
                    oss << "x";
                } else {
                    char c = *reinterpret_cast<char*>(lb.m_data.get() + current_offset);

                    if (' ' <= c && c <= 127) {
                        oss << c;
                    } else {
                        oss << ".";
                    }
                }
            }

            oss << s.get_box_character(0u) << std::endl;
        }

        {
            // Footer
            for (uint16_t depth = 0u; depth < s.get_depth(); depth++) {
                oss << s.get_box_character(0u) << std::string(s.get_lon_indent_width() - 1u, ' '); // Indent
            }

            oss << s.get_box_character(4u);

            for (std::size_t i = 0; i < offset_width; i++) {
                oss << s.get_box_character(1u);
            }

            oss << s.get_box_character(9u);

            for (std::size_t i = 0; i < number_of_bytes_per_row * 3u - 1u; i++) {
                oss << s.get_box_character(1u);
            }

            oss << s.get_box_character(9u);

            for (std::size_t i = 0; i < number_of_bytes_per_row; i++) {
                oss << s.get_box_character(1u);
            }

            oss << s.get_box_character(5u) << std::endl;
        }

        s.decrement_depth();

        for (uint16_t depth = 0u; depth < s.get_depth(); depth++) {
            oss << s.get_box_character(0u) << std::string(s.get_lon_indent_width() - 1u, ' '); // Indent
        }
        oss << ">";

        return oss.str();
    }

#ifdef PROJECT_NAMESPACE
}
#endif