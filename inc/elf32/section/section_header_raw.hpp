#ifndef ELF_CRAFTER_SECTION_HEADER_RAW_HPP
#define ELF_CRAFTER_SECTION_HEADER_RAW_HPP

#include <config.hpp>

#include <elf32/type.hpp>
#include <utility/stringifier.hpp>

#include "type.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        struct section_attribute_flags
        {
            enum struct enum_section_attribute : elf32_word::type
            {
                WRITEABLE                         = 1u,
                ALLOC                             = 2u,
                EXECUTABLE                        = 4u,
                PROCESSOR_SPECIFIC_SEMANTICS_MASK = 0xf0000000,
            };

            friend const lon_type* operator|(enum_section_attribute section_attribute, const lonifier& l);

            constexpr section_attribute_flags() {}

            bool is_set(enum_section_attribute attribute) const;
            void set(enum_section_attribute attribute);

            friend const lon_type* operator|(const section_attribute_flags& flags, const lonifier& l);

        private:
            elf32_word m_flags = 0;
        };

        struct section_header_raw
        {
            constexpr section_header_raw()
                : index_section_name(0u),
                  section_type(enum_section_type::NULL_TYPE),
                  address(0u),
                  file_offset(0u),
                  size(0u),
                  link_section_index(),
                  info(),
                  address_alignment(0u),
                  entry_size(0u)

            {}

            section_header_raw(const std::byte* bytes);

            elf32_word index_section_name;

            enum_section_type       section_type;
            section_attribute_flags flags;

            elf32_address address;
            elf32_offset  file_offset;
            elf32_word    size;

            /*
    | Section Type | Link                         | Info |
    | DYNAMIC      | The section header index     | 0
                    | of the string table used by  |
                    | entries in the section.      |
    ---------------------------------------------------------
    | HASH         | The section header index     |
                    | of the symbol table to       |
                    | which the hash table applies. |
    -----------------------------------------------------------
    | RELOCATION   | The section header index of  | The section header index
                    the assicoated symbol table.  | of the section to which
                                                    the reolcation applies.
    | RELOCATION_WITH_ADDENDS |
    ---------------------------------------------------------------------

    | SYMBOL_TABLE
            */
            elf32_word link_section_index;
            elf32_word info;

            elf32_word address_alignment;
            elf32_word entry_size;
        };
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
} // namespace elf_crafter
#endif

#endif