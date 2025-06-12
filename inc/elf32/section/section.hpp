#ifndef SECTION_HPP
#define SECTION_HPP

#include "config.hpp"
#include "elf32/types.hpp"
#include "section_header_table/section_header.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        enum struct enum_special_section_indexes : elf32_word
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

        private:
            section_header* m_ptr_section_header;
        };
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
}
#endif

#endif