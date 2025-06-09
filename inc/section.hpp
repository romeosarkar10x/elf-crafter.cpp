#ifndef SECTION_HPP
#define SECTION_HPP

#include "elf_types.hpp"

namespace elf_crafter
{
    enum enum_special_section_indexes : elf32_word
    {
        UNDEFINED = 0u,
        RESERVED_LOW = 0xff00u,
        PROCESSOR_SPECIFIC_SEMANTICS_LOW = 0xff00u,
        PROCESSOR_SPECIFIC_SEMANTICS_HIGH = 0xff1fu,
        ABSOLUTE = 0xfff1u,
        COMMON = 0xfff2u,
        RESERVED_HIGH = 0xffffu,
    };
}

#endif