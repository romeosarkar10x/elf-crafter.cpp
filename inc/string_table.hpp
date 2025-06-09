#ifndef STRING_TABLE_HPP
#define STRING_TABLE_HPP

#include "elf_types.hpp"

namespace elf_crafter
{
    struct string_table
    {
        const char* at(elf32_offset index) const;
        char* at(elf32_offset index);

    private:
        char* m_ptr;
    };
} // namespace elf_crafter

#endif