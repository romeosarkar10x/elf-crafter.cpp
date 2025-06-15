#include <sstream>

#include <elf32/type.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        const lon_type* operator|(const elf32_address& address, const lonifier& l)
        {
            std::ostringstream oss;
            oss << "0x" << std::hex << address.value;
            return new lon_string(oss.str());
        }

        const lon_type* operator|(const elf32_half& half, const lonifier& l)
        {
            std::ostringstream oss;
            oss << "0x" << std::hex << half.value;
            return new lon_string(oss.str());
        }

        const lon_type* operator|(const elf32_offset& offset, const lonifier& l)
        {
            std::ostringstream oss;
            oss << "0x" << std::hex << offset.value;
            return new lon_string(oss.str());
        }

        const lon_type* operator|(const elf32_word& word, const lonifier& l)
        {
            std::ostringstream oss;
            oss << word.value;
            return new lon_string(oss.str());
        }
    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif
