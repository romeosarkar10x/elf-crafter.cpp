#include "elf32/version.hpp"

#include <stdexcept>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        const lon_type* operator|(enum_elf_version elf_version, const lonifier& l)
        {
            switch (elf_version) {
            case enum_elf_version::NONE:
                return new lon_string("None");

            case enum_elf_version::CURRENT:
                return new lon_string("Current");
            }

            throw std::runtime_error("invalid elf_version");
        }

    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif