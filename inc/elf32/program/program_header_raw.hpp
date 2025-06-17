#pragma once

#include <config.hpp>

#include <elf32/type.hpp>
#include <utility/lonifier/lonifier.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        enum struct enum_segment_type : elf32_word::type
        {
            TYPE_NULL,
            LOAD,
            DYNAMIC,
            INTERPRETER,
            NOTE,
            RESERVED,
            PROGRAM_HEADER,
            LOW_PROC  = 0x70000000u,
            HIGH_PROC = 0x7fffffffu,
        };

        const lon_type* operator|(enum_segment_type segment_type, const lonifier& l);

        enum enum_segment_permission : elf32_word::type
        {
            NONE,
            EXECUTE = 1u,
            WRITE   = 2u,
            READ    = 4u,
        };

        const lon_type* operator|(enum_segment_permission segment_permission, const lonifier& l);

        struct segment_permission_flags
        {
            bool is_set(enum_segment_permission segment_permission) const;
            void set(enum_segment_permission segment_permission);

            friend const lon_type* operator|(
                const segment_permission_flags& segment_permission_flags_obj, const lonifier& l
            );

        private:
            elf32_word m_flags;
        };

        struct program_header_raw
        {
            enum_segment_type segment_type;
            elf32_offset      file_offset;

            elf32_address virtual_address;
            elf32_address physical_address;

            elf32_word size_in_file;
            elf32_word size_in_memory;

            segment_permission_flags flags;
            elf32_word               alignment;

            friend const lon_type* operator|(
                const program_header_raw& program_header_raw_obj, const lonifier& lonifier_obj
            );
        };

    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif
