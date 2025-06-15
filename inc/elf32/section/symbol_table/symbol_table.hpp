/*
#pragma once

#include <vector>

#include "config.hpp"
#include "elf32/section/section.hpp"
#include "symbol_table_entry_raw.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        struct symbol_table : public section
        {
            symbol_table_entry_raw at(elf32_offset index);

        private:
        };

    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif
*/