#include "utility/stringifier.hpp"

#include "utility/lonifier/lon_type.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    stringifier::stringifier() {}

    stringifier::stringifier(uint16_t lon_indent_width) : m_lon_indent_width{lon_indent_width} {}

    uint16_t stringifier::get_lon_indent_width() const
    {
        return m_lon_indent_width;
    }

    void stringifier::increment_depth() const
    {
        m_depth++;
    }

    void stringifier::decrement_depth() const
    {
        m_depth--;
    }

    uint16_t stringifier::get_depth() const
    {
        return m_depth;
    }

#ifdef PROJECT_NAMESPACE
}
#endif