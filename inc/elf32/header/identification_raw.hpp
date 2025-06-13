#ifndef ELF_CRAFTER_ELF_IDENTIFICATION
#define ELF_CRAFTER_ELF_IDENTIFICATION

#include "config.hpp"
#include "elf32/type.hpp"
#include "elf32/version.hpp"
#include "utility/compare.hpp"
#include "utility/lonifier/lonifier.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        struct identification_raw
        {
            enum enum_identification_indexes : elf32_offset::type
            {
                MAGIC_NUMBER_0,
                MAGIC_NUMBER_1,
                MAGIC_NUMBER_2,
                MAGIC_NUMBER_3,
                FILE_CLASS,
                DATA_ENCODING,
                FILE_VERSION,
                START_OF_PADDING_BYTES,
                SIZE_OF_IDENTIFICATION = 16u
            };

            enum struct enum_file_class : elf32_unsigned_char
            {
                NONE,
                CLASS_32,
                CLASS_64,
            };

            friend const lon_type* operator|(enum_file_class file_class, const lonifier& l);

            enum struct enum_data_encoding : elf32_unsigned_char
            {
                NONE,
                LITTLE_ENDIAN_ORDER,
                BIG_ENDIAN_ORDER, /* TODO: Implement big-endian data encoding format. */
            };

            friend const lon_type* operator|(enum_data_encoding data_encoding, const lonifier& l);

            identification_raw();
            identification_raw(const std::byte* bytes);
            identification_raw(
                enum_file_class file_class, enum_data_encoding data_encoding, enum_elf_version file_version
            );

            elf32_unsigned_char get(enum_identification_indexes index) const;
            elf32_unsigned_char get(elf32_offset index) const;

            void set(enum_identification_indexes index, elf32_unsigned_char value);
            void set(elf32_offset index, elf32_unsigned_char value);

            enum_file_class get_file_class() const;
            void            set_file_class(enum_file_class file_class);

            enum_data_encoding get_data_encoding() const;
            void               set_data_encoding(enum_data_encoding data_encoding);

            enum_elf_version get_elf_version() const;
            void             set_elf_version(enum_elf_version elf_version);

            friend const lon_type* operator|(const identification_raw& identification, const lonifier& l);

        private:
            elf32_unsigned_char
                m_bytes[static_cast<unsigned long>(enum_identification_indexes::SIZE_OF_IDENTIFICATION)];
        };

    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif

#endif