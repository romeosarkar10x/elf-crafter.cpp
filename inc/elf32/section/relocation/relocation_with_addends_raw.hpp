#pragma once

#include <config.hpp>

#include <elf32/section/relocation/relocation_info_raw.hpp>
#include <elf32/type.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        struct relocation_with_addends_raw
        {
            elf32_address       offset;
            relocation_info_raw info;
            elf32_signed_word   addend;
        };

    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif