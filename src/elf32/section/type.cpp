#include <stdexcept>

#include <elf32/section/type.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        const lon_type* operator|(enum_section_type section_type, const lonifier& l)
        {
            switch (section_type) {
            case enum_section_type::NULL_TYPE:
                return new lon_string("Null");

            case enum_section_type::PROGRAM_BITS:
                return new lon_string("Program bits");

            case enum_section_type::SYMBOL_TABLE:
                return new lon_string("Symbol-table");

            case enum_section_type::STRING_TABLE:
                return new lon_string("String-table");

            case enum_section_type::RELOCATION_WITH_ADDENDS:
                return new lon_string("Relocation with addends");

            case enum_section_type::HASH:
                return new lon_string("Hash");

            case enum_section_type::DYNAMIC:
                return new lon_string("Dynamic");

            case enum_section_type::NOTE:
                return new lon_string("Note");

            case enum_section_type::NO_BITS:
                return new lon_string("No bits");

            case enum_section_type::RELOCATION:
                return new lon_string("Relocation");

            case enum_section_type::LIB:
                return new lon_string("Lib");

            case enum_section_type::DYNAMIC_SYMBOL:
                return new lon_string("Dynamic symbol");

            default:
                throw std::runtime_error("Unhandled `section_type`");
            }

            throw std::runtime_error("Invalid `section_type`");
        }

    } // namespace elf32
#ifdef PROJECT_NAMESPACE
}
#endif
