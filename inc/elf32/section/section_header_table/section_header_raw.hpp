#ifndef ELF_CRAFTER_SECTION_HEADER_RAW_HPP
#define ELF_CRAFTER_SECTION_HEADER_RAW_HPP

#include <config.hpp>

#include <elf32/section/type.hpp>
#include <elf32/type.hpp>
#include <utility/stringifier.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        struct section_header_raw
        {
            friend const std::string operator|(enum_section_type section_type, const stringifier& s);

            struct section_attribute_flags
            {
                enum struct enum_section_attribute : elf32_word::type
                {
                    WRITEABLE = 1u,
                    ALLOC,
                    EXECUTABLE,
                    PROCESSOR_SPECIFIC_SEMANTICS_MASK,
                };

                constexpr section_attribute_flags() : m_flags(0u) {}

                void is_set(enum_section_attribute attribute);
                void set(enum_section_attribute attribute);

            private:
                elf32_word m_flags;
            };

            constexpr section_header_raw()
                : m_index_section_name(0u),
                  m_section_type(enum_section_type::NULL_TYPE),
                  m_address(0u),
                  m_file_offset(0u),
                  m_size(0u),
                  m_link_section_index(),
                  m_info(),
                  m_address_alignment(0u),
                  m_entry_size(0u)

            {}

            section_header_raw(const std::byte* bytes);

            // const char* get_index_section_name() const;
            // void        set_section_name();

            enum_section_type get_section_type() const;
            void              set_section_type(enum_section_type section_type);

        private:
            elf32_word m_index_section_name;

            enum_section_type       m_section_type;
            section_attribute_flags m_flags;

            elf32_address m_address;
            elf32_offset  m_file_offset;
            elf32_word    m_size;

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
            elf32_word m_link_section_index;
            elf32_word m_info;

            elf32_word m_address_alignment;
            elf32_word m_entry_size;
        };
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
} // namespace elf_crafter
#endif

#endif