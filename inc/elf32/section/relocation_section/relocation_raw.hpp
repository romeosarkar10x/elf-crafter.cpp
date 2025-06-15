#pragma once

#include "config.hpp"
#include "elf32/type.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        struct relocation_raw
        {
            elf32_address offset;
            elf32_word    info;
        };
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif