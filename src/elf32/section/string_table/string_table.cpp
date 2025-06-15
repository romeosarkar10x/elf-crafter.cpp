#include <elf32/section/string_table/string_table.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    namespace elf32
    {
        const char* string_table::get(elf32_word index) const
        {
            return const_cast<string_table*>(this)->get(index);
        }

        char* string_table::get(elf32_word index)
        {
            return reinterpret_cast<char*>(m_bytes.get() + index);
        }

    } // namespace elf32

#ifdef PROJECT_NAMESPACE
}
#endif