#include "utility/lonifier/lon_string.hpp"

#include <iostream>

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    lon_string::lon_string(const std::string& value) : m_value(value) {}

    lon_string::enum_lon_type lon_string::get_type() const
    {
        return enum_lon_type::STRING;
    }

    lon_string operator+(const lon_string& ls, const char* c_str)
    {
        return ls.m_value + c_str;
    }

    std::string operator|(const lon_string& ls, const stringifier& s)
    {
        return ls.m_value;
    }

#ifdef PROJECT_NAMESPACE
}
#endif