#include <climits>
#include <stdexcept>
#include <unistd.h>

#include <elf32/header/header_raw.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        const lon_type* operator|(header_raw::enum_object_type object_type, const lonifier& l)
        {
            switch (object_type) {
            case header_raw::enum_object_type::NONE:
                return new lon_string("None");

            case header_raw::enum_object_type::RELOCATABLE:
                return new lon_string("Relocatable");

            case header_raw::enum_object_type::EXECUTABLE:
                return new lon_string("Executable");

            case header_raw::enum_object_type::SHARED_OBJECT:
                return new lon_string("Shared object");

            case header_raw::enum_object_type::CORE:
                return new lon_string("Core");

            case header_raw::enum_object_type::LO_PROCESSOR_SPECIFIC:
                return new lon_string("Low (processor specific)");

            case header_raw::enum_object_type::HI_PROCESSOR_SPECIFIC:
                return new lon_string("High (processor specific)");
            }

            throw std::runtime_error("invalid object_type");
        }

        const lon_type* operator|(header_raw::enum_machine_type machine_type, const lonifier& l)
        {
            switch (machine_type) {
            case header_raw::enum_machine_type::NONE:
                return new lon_string("None");

            case header_raw::enum_machine_type::M32:
                return new lon_string("M32");

            case header_raw::enum_machine_type::SPARC:
                return new lon_string("SPARC");

            case header_raw::enum_machine_type::INTEL_386:
                return new lon_string("Intel 386");

            case header_raw::enum_machine_type::MOTOROLA_68K:
                return new lon_string("MOTOROLA_68K");

            case header_raw::enum_machine_type::MOTOROLA_88K:
                return new lon_string("MOTOROLA_88K");

            case header_raw::enum_machine_type::INTEL_80860:
                return new lon_string("INTEL_80860");

            case header_raw::enum_machine_type::MIPS_RS3000_BIG_ENDIAN:
                return new lon_string("IPS_RS3000_BIG_ENDIAN");

            case header_raw::enum_machine_type::MIPS_RS4000_BIG_ENDIAN:
                return new lon_string("MIPS_RS4000_BIG_ENDIAN");

            case header_raw::enum_machine_type::RESERVED_11:
                return new lon_string("RESERVED_11");

            case header_raw::enum_machine_type::RESERVED_12:
                return new lon_string("RESERVED_12");

            case header_raw::enum_machine_type::RESERVED_13:
                return new lon_string("RESERVED_13");

            case header_raw::enum_machine_type::RESERVED_14:
                return new lon_string("RESERVED_14");

            case header_raw::enum_machine_type::RESERVED_15:
                return new lon_string("RESERVED_15");

            case header_raw::enum_machine_type::RESERVED_16:
                return new lon_string("RESERVED_16");
            };

            throw std::runtime_error("Invalid `machine_type`");
        }

        header_raw::header_raw(const std::byte* const bytes) : identification{bytes}
        {
            const header_raw& h_raw = *reinterpret_cast<const header_raw*>(bytes);

            // TODO: Validate each field.
            {
                // Validate `machine`
            }

            {
                // Validate `version`
            }

            {
                // Validate `entry_point`
            }

            {
                // Validate `program_header_offset`
            }

            {
                // Validate `section_header_offset`
            }

            {
                // Validate `flags`
            }

            {
                // Validate `elf_header_size`
            }

            {
                // Validate `program_header_entry_size`
            }

            {
                // Validate `program_header_number_of_entries`
            }

            {
                // Validate `section_header_entry_size`
            }

            {
                // Validate `section_header_number_of_entries`
            }

            {
                // Validate `section_name_string_table_index`
            }

            object_type = h_raw.object_type;
            machine     = h_raw.machine;
            version     = h_raw.version;
            entry_point = h_raw.entry_point;

            program_header_offset = h_raw.program_header_offset;
            section_header_offset = h_raw.section_header_offset;

            flags = h_raw.flags;

            elf_header_size = h_raw.elf_header_size;

            program_header_entry_size        = h_raw.program_header_entry_size;
            program_header_number_of_entries = h_raw.program_header_number_of_entries;

            section_header_entry_size        = h_raw.section_header_entry_size;
            section_header_number_of_entries = h_raw.section_header_number_of_entries;

            section_name_string_table_index = h_raw.section_name_string_table_index;
        }
    } // namespace elf32
#ifdef PROJECT_NAMESPACE
}
#endif