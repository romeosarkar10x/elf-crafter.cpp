#pragma once

#include "config.hpp"
#include "elf32/type.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        struct relocation_with_addends_raw
        {
        private:
            elf32_address     offset;
            elf32_word        info;
            elf32_signed_word addend;
        };

    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif