#include <iostream>
#include <sstream>

#include <elf32/program/program_header_raw.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        const lon_type* operator|(const enum_segment_type segment_type, const lonifier& l)
        {
            switch (segment_type) {
            case enum_segment_type::TYPE_NULL:
                return new lon_string("Null");

            case enum_segment_type::LOAD:
                return new lon_string("Load");

            case enum_segment_type::DYNAMIC:
                return new lon_string("Dynamic");

            case enum_segment_type::INTERPRETER:
                return new lon_string("Interpreter");

            case enum_segment_type::NOTE:
                return new lon_string("Note");

            case enum_segment_type::RESERVED:
                return new lon_string("Reserved");

            case enum_segment_type::PROGRAM_HEADER:
                return new lon_string("Program-header");

            default:
                std::cout << static_cast<uint32_t>(segment_type) << std::endl;
                throw std::runtime_error("Unhandled `segment_type`");
            }

            throw std::runtime_error("Invalid `segment_type`");
        }

        const lon_type* operator|(const enum_segment_permission segment_permission, const lonifier& l)
        {
            switch (segment_permission) {
            case enum_segment_permission::NONE:
                return new lon_string("None");

            case enum_segment_permission::EXECUTE:
                return new lon_string("Execute");

            case enum_segment_permission::WRITE:
                return new lon_string("Write");

            case enum_segment_permission::READ:
                return new lon_string("Read");

            default:
                throw std::runtime_error("Unhandled `segment_permission`");
            }

            throw std::runtime_error("Invalid `segment_permission`");
        }

        bool segment_permission_flags::is_set(const enum_segment_permission segment_permission) const
        {
            return (m_flags & segment_permission) != 0;
        }

        const lon_type* operator|(const segment_permission_flags& flags, const lonifier& l)
        {
            std::ostringstream oss;

            if (flags.is_set(enum_segment_permission::READ)) {
                oss << "Read";
            }

            if (flags.is_set(enum_segment_permission::WRITE)) {
                oss << (!oss.str().empty() ? " " : "") << "Write";
            }

            if (flags.is_set(enum_segment_permission::EXECUTE)) {
                oss << (!oss.str().empty() ? " " : "") << "Execute";
            }

            if (oss.str().empty()) {
                oss << "None";
            }

            return new lon_string(oss.str());
        }

        const lon_type* operator|(const program_header_raw& program_header_raw_obj, const lonifier& l)
        {
            lon_object* lo = new lon_object;

            lo->set_key("Segment type", program_header_raw_obj.segment_type | l);
            lo->set_key("File offset", program_header_raw_obj.file_offset | l);

            lo->set_key("Virtual address", program_header_raw_obj.virtual_address | l);
            lo->set_key("Physical address", program_header_raw_obj.physical_address | l);

            lo->set_key("Size (file)", program_header_raw_obj.size_in_file | l);
            lo->set_key("Size (memory)", program_header_raw_obj.size_in_memory | l);

            lo->set_key("Flags", program_header_raw_obj.flags | l);
            lo->set_key("Alignment", program_header_raw_obj.alignment | l);

            return lo;
        }
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif