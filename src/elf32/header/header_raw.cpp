#include "elf32/header/header_raw.hpp"

#include <climits>
#include <stdexcept>
#include <unistd.h>

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

        header_raw::header_raw(int file_descriptor)
        {
            if (file_descriptor == -1) {
                throw std::runtime_error("file_descriptor == -1");
            }

            off_t last_offset = lseek(file_descriptor, 0, SEEK_CUR);

            if (last_offset == -1) {
                // TODO: Handle errors.
                if (errno == EBADF) {
                } else if (errno == EINVAL) {
                } else if (errno == ENXIO) {
                } else if (errno == EOVERFLOW) {
                } else if (errno == ESPIPE) {
                }

                throw std::runtime_error("unable to get last_offset");
            }

            {
                off_t offset = lseek(file_descriptor, 0, SEEK_SET);

                if (offset == -1) {
                    // TODO: Handle errors.
                    if (errno == EBADF) {
                    } else if (errno == EINVAL) {
                    } else if (errno == ENXIO) {
                    } else if (errno == EOVERFLOW) {
                    } else if (errno == ESPIPE) {
                    }

                    throw std::runtime_error("Unable to seek to offset 0 (absolute)");
                }
            }

            std::byte* buffer = reinterpret_cast<std::byte*>(this);

            size_t number_of_bytes_read    = 0;
            size_t number_of_bytes_to_read = sizeof(header_raw);

            while (number_of_bytes_to_read) {
                ssize_t current_number_of_bytes_read =
                    read(file_descriptor, buffer + number_of_bytes_read, number_of_bytes_to_read);

                if (current_number_of_bytes_read == 0) {
                    throw std::runtime_error("unexpected end of file!");
                } else if (current_number_of_bytes_read == -1) {
                    if (errno != EAGAIN) {
                        throw std::runtime_error("error reading at header_raw");
                    }
                }

                number_of_bytes_read += current_number_of_bytes_read;
                number_of_bytes_to_read -= current_number_of_bytes_read;
            }

            new (&m_identification) identification_raw(buffer);

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
        }

        const lon_type* operator|(const header_raw& h_raw, const lonifier& l)
        {
            lon_object* lo = new lon_object;

            lo->set_key("Identification", h_raw.m_identification | l);
            lo->set_key("Object type", h_raw.m_object_type | l);
            lo->set_key("Machine", h_raw.m_machine | l);

            // lo->set_key("Version", );
            lo->set_key("Entry point", h_raw.m_entry_point | l);
            lo->set_key("Program-header offset", h_raw.m_program_header_offset | l);
            lo->set_key("Section-header offset", h_raw.m_section_header_offset | l);

            // TODO: implement elf-header flags
            // lo->set_key("Flags: ")

            lo->set_key("ELF header size", (h_raw.m_elf_header_size.value | l));

            lo->set_key("Program-header entry size", h_raw.m_program_header_entry_size.value | l);
            lo->set_key("Program-header number of entries", h_raw.m_program_header_number_of_entries.value | l);

            lo->set_key("Section-header entry size", h_raw.m_section_header_entry_size.value | l);
            lo->set_key("Section-header number of entries", h_raw.m_section_header_number_of_entries.value | l);

            lo->set_key(
                "Section-name string-table index", std::to_string(h_raw.m_section_name_string_table_index.value) | l
            );

            return lo;
        }

        elf32_offset header_raw::get_program_header_offset() const
        {
            return m_program_header_offset;
        }

        elf32_offset header_raw::get_section_header_offset() const
        {
            return m_section_header_offset;
        }

        elf32_half header_raw::get_section_header_number_of_entries() const
        {
            return m_section_header_number_of_entries;
        }

        elf32_half header_raw::get_section_header_entry_size() const
        {
            return m_section_header_entry_size;
        }

    } // namespace elf32
#ifdef PROJECT_NAMESPACE
}
#endif