#pragma once

#include <config.hpp>

#include <elf32/section/section.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        struct relocation_section : public section
        {
        private:
        };

    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif
