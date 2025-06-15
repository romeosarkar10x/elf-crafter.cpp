#include <iostream>
#include <sstream>
#include <stdexcept>

#include <elf32/section/section_header_raw.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        bool section_header_raw::section_attribute_flags::is_set(const enum_section_attribute section_attribute) const
        {
            return (
                (m_flags.value & static_cast<std::underlying_type_t<enum_section_attribute>>(section_attribute)) != 0
            );
        }

        section_header_raw::section_header_raw(const std::byte* bytes)
        {
            const section_header_raw& section_header = *reinterpret_cast<const section_header_raw*>(bytes);

            {
                // TODO: Validate all fields
            }

            index_section_name = section_header.index_section_name;
            section_type       = section_header.section_type;
            address            = section_header.address;
            file_offset        = section_header.file_offset;
            size               = section_header.size;
            link_section_index = section_header.link_section_index;
            info               = section_header.info;
            address_alignment  = section_header.address_alignment;
            entry_size         = section_header.entry_size;
        }

        const lon_type* operator|(
            const section_header_raw::section_attribute_flags::enum_section_attribute section_attribute,
            const lonifier&                                                           l
        )
        {
            switch (section_attribute) {
            case section_header_raw::section_attribute_flags::enum_section_attribute::WRITEABLE:
                return new lon_string("Writeable");

            case section_header_raw::section_attribute_flags::enum_section_attribute::ALLOC:
                return new lon_string("Alloc");

            case section_header_raw::section_attribute_flags::enum_section_attribute::EXECUTABLE:
                return new lon_string("Executable");

            default:
                throw std::runtime_error("Unhandled `section_attribute`");
            }

            throw std::runtime_error("Invalid `section_attribute`");
        }

        const lon_type* operator|(
            const section_header_raw::section_attribute_flags& section_attributes, const lonifier& l
        )
        {
            std::ostringstream oss;

            if (section_attributes.is_set(section_header_raw::section_attribute_flags::enum_section_attribute::WRITEABLE
                )) {
                oss << (oss.str().empty() ? "" : " ")
                    << (section_header_raw::section_attribute_flags::enum_section_attribute::WRITEABLE | lonifier() |
                        stringifier());
            }

            if (section_attributes.is_set(section_header_raw::section_attribute_flags::enum_section_attribute::ALLOC)) {
                oss << (oss.str().empty() ? "" : " ")
                    << (section_header_raw::section_attribute_flags::enum_section_attribute::ALLOC | lonifier() |
                        stringifier());
            }

            if (section_attributes.is_set(
                    section_header_raw::section_attribute_flags::enum_section_attribute::EXECUTABLE
                )) {
                oss << (oss.str().empty() ? "" : " ")
                    << (section_header_raw::section_attribute_flags::enum_section_attribute::EXECUTABLE | lonifier() |
                        stringifier());
            }

            if (oss.str().empty()) {
                oss << "None";
            }

            return new lon_string(oss.str());
        }
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif