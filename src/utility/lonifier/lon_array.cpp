#include "utility/lonifier/lon_array.hpp"

#include <sstream>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    lon_array::lon_array() {};

    void lon_array::push(lon_type* object)
    {
        m_data.push_back(object);
    }

    void lon_array::pop()
    {
        m_data.pop_back();
    }

    const std::vector<lon_type*>& lon_array::get_values() const
    {
        return m_data;
    }

    lon_array::enum_lon_type lon_array::get_type() const
    {
        return enum_lon_type::ARRAY;
    }

    std::string operator|(const lon_array& la, const stringifier& s)
    {
        std::ostringstream oss;
        oss << "[" << std::endl;

        s.increment_depth();

        for (auto&& value : la.get_values()) {
            for (uint16_t depth = 0u; depth < s.get_depth(); depth++) {
                oss << s.get_box_character(0u) << std::string(s.get_lon_indent_width() - 1u, ' '); // Indent
            }

            oss << (value | s) << std::endl;
        }

        s.decrement_depth();

        for (uint16_t depth = 0u; depth < s.get_depth(); depth++) {
            oss << s.get_box_character(0u) << std::string(s.get_lon_indent_width() - 1u, ' '); // Indent
        }
        oss << "]";
        return oss.str();
    }

#ifdef PROJECT_NAMESPACE
}
#endif
