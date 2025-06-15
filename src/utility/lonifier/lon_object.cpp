#include <iostream>
#include <sstream>

#include <utility/lonifier/lon_object.hpp>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    lon_object::lon_object() {}

    const lon_type* lon_object::get_key(const std::string& key) const
    {
        // TODO: Handle exceptional case when key does not exist!
        return m_data.at(key);
    }

    void lon_object::set_key(const std::string& key, const lon_type* const object)
    {
        m_data.emplace(key, object);
    }

    const std::map<std::string, const lon_type*>& lon_object::get_key_value_map() const
    {
        return m_data;
    }

    lon_object::enum_lon_type lon_object::get_type() const
    {
        return enum_lon_type::OBJECT;
    }

    std::string operator|(const lon_object& lo, const stringifier& s)
    {
        std::ostringstream ostringstream;
        ostringstream << "{" << std::endl;

        s.increment_depth();

        auto& key_value_map = lo.get_key_value_map();

        for (auto& [key, value] : lo.get_key_value_map()) {
            for (uint16_t depth = 0u; depth < s.get_depth(); depth++) {
                ostringstream << s.get_box_character(0u) << std::string(s.get_lon_indent_width() - 1u, ' '); // Indent
            }

            ostringstream << key << ": " << (value | s) << std::endl;
        }

        s.decrement_depth();

        for (uint16_t depth = 0u; depth < s.get_depth(); depth++) {
            ostringstream << s.get_box_character(0u) << std::string(s.get_lon_indent_width() - 1u, ' '); // Indent
        }
        ostringstream << "}";
        return ostringstream.str();
    }

#ifdef PROJECT_NAMESPACE
}
#endif
