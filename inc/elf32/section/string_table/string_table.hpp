#ifndef STRING_TABLE_HPP
#define STRING_TABLE_HPP

#include "config.hpp"
#include "elf32/section/section.hpp"
#include "elf32/type.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        struct string_table : public section
        {
            const char* at(elf32_offset index) const;
            char*       at(elf32_offset index);

        private:
            char* m_ptr;
        };

    } // namespace elf32
#ifdef PROJECT_NAMESPACE
} // namespace elf_crafter
#endif

#endif