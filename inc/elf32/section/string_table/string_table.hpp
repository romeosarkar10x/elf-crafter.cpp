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
            using section::section;

            const char* get(elf32_word index) const;
            char*       get(elf32_word index);
        };

    } // namespace elf32
#ifdef PROJECT_NAMESPACE
} // namespace elf_crafter
#endif

#endif