#ifndef SECTION_HPP
#define SECTION_HPP

#include <config.hpp>
#include <memory>

#include <elf32/forward_declaration.hpp>
#include <elf32/section/type.hpp>
#include <elf32/type.hpp>

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
            section();
            section(
                elf32* elf, enum_section_type type, const char* name, elf32_address address,
                elf32_word address_alignment, elf32_word size, std::unique_ptr<std::byte> bytes
            );

            const std::byte* get_bytes() const;
            std::byte*       get_bytes();

            void set_bytes(const std::byte* bytes, elf32_word size);

            friend const lon_type* operator|(const section& s, const lonifier& l);

        protected:
            elf32* m_elf;

            enum_section_type m_type;
            std::string       m_name;

            elf32_address m_address;
            elf32_word    m_address_alignment;

            elf32_word                 m_size;
            std::unique_ptr<std::byte> m_bytes;
        };
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
}
#endif

#endif