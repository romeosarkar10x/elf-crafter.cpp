#include "elf32/header/identification_raw.hpp"

#include <sstream>
#include <stdexcept>

#include "elf32/header/header_raw.hpp"
#include "elf32/version.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    namespace elf32
    {
        identification_raw::identification_raw() {}

        identification_raw::identification_raw(std::byte* bytes)
        {
            // TODO: Validate each field!
            {
                // Validate `MAGIC_NUMBER_0`
                const elf32_unsigned_char magic_number_0 = static_cast<elf32_unsigned_char>(
                    bytes[enum_identification_indexes::MAGIC_NUMBER_0]
                );

                if (magic_number_0 != 0x7fu) {
                    throw std::runtime_error("invalid magic_number_0");
                }
            }

            {
                // Validate `MAGIC_NUMBER_1`
                const elf32_unsigned_char magic_number_1 = static_cast<elf32_unsigned_char>(
                    bytes[enum_identification_indexes::MAGIC_NUMBER_1]
                );

                if (magic_number_1 != 0x45u) {
                    throw std::runtime_error("invalid magic_number_1");
                }
            }

            {
                // Validate `MAGIC_NUMBER_2`
                const elf32_unsigned_char magic_number_2 = static_cast<elf32_unsigned_char>(
                    bytes[enum_identification_indexes::MAGIC_NUMBER_2]
                );

                if (magic_number_2 != 0x4cu) {
                    throw std::runtime_error("invalid magic_number_2");
                }
            }

            {
                // Validate `MAGIC_NUMBER_3`
                const elf32_unsigned_char magic_number_3 = static_cast<elf32_unsigned_char>(
                    bytes[enum_identification_indexes::MAGIC_NUMBER_3]
                );

                if (magic_number_3 != 0x46u) {
                    throw std::runtime_error("invalid magic_number_3");
                }
            }

            {
                // Validate `FILE_CLASS`
                const elf32_unsigned_char file_class = static_cast<elf32_unsigned_char>(
                    bytes[enum_identification_indexes::FILE_CLASS]
                );

                if (file_class != enum_file_class::CLASS_32) {
                    throw std::runtime_error("cannot parse this file_class");
                }
            }

            {
                // Validate `DATA_ENCODING`
                const elf32_unsigned_char data_encoding = static_cast<elf32_unsigned_char>(
                    bytes[enum_identification_indexes::DATA_ENCODING]
                );

                if (data_encoding != enum_data_encoding::LITTLE_ENDIAN_ORDER) {
                    throw std::runtime_error("cannot parse this data_encoding");
                }
            }

            {
                // Validate `FILE_VERSION`
                const elf32_unsigned_char elf_version = static_cast<elf32_unsigned_char>(
                    bytes[enum_identification_indexes::FILE_VERSION]
                );

                if (elf_version != enum_elf_version::CURRENT) {
                    throw std::runtime_error("invalid elf version");
                }
            }

            {
                // Validate `START_OF_PADDING_BYTES`
            }

            std::copy(
                bytes, bytes + SIZE_OF_IDENTIFICATION, reinterpret_cast<std::byte*>(&m_bytes)
            );
        }

        elf32_unsigned_char identification_raw::get(enum_identification_indexes index) const
        {
            return m_bytes[index];
        }

        const lon_type* operator|(const identification_raw& identification, const lonifier& l)
        {
            lon_object*        lo = new lon_object;
            std::ostringstream ostringstream;

            ostringstream << std::hex
                          << static_cast<uint32_t>(identification.get(
                                 identification_raw::enum_identification_indexes::MAGIC_NUMBER_0
                             ))
                          << " ";
            ostringstream << std::hex
                          << static_cast<uint32_t>(identification.get(
                                 identification_raw::enum_identification_indexes::MAGIC_NUMBER_1
                             ))
                          << " ";
            ostringstream << std::hex
                          << static_cast<uint32_t>(identification.get(
                                 identification_raw::enum_identification_indexes::MAGIC_NUMBER_2
                             ))
                          << " ";
            ostringstream << std::hex
                          << static_cast<uint32_t>(identification.get(
                                 identification_raw::enum_identification_indexes::MAGIC_NUMBER_3
                             ))
                          << " ";

            return lo;
        }

    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif