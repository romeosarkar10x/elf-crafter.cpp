#ifndef SECTION_HPP
#define SECTION_HPP

#include "config.hpp"
#include "elf32/forward_declaration.hpp"
#include "elf32/type.hpp"
#include "section_header_table/section_header_raw.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        enum struct enum_special_section_indexes : elf32_half::type
        {
            UNDEFINED                         = 0u,
            RESERVED_LOW                      = 0xff00u,
            PROCESSOR_SPECIFIC_SEMANTICS_LOW  = 0xff00u,
            PROCESSOR_SPECIFIC_SEMANTICS_HIGH = 0xff1fu,
            ABSOLUTE                          = 0xfff1u,
            COMMON                            = 0xfff2u,
            RESERVED_HIGH                     = 0xffffu,
        };

        struct section
        {
            const std::byte* get_bytes() const;
            std::byte*       get_bytes();

            void set_bytes(const std::byte* bytes, elf32_word size);

            static std::map<enum_section_type, std::vector<section>> create_sections_map();

        private:
            elf32* m_elf;

            enum_section_type m_type;
            std::string       m_name;

            elf32_address m_address;
            elf32_offset  m_file_offset;

            elf32_word m_size;
            std::byte* m_bytes;

            section* m_link;
        };
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
}
#endif

#endif