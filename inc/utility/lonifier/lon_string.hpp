#ifndef ELF_PARSER_LONIFY_LON_STRING_HPP
#define ELF_PARSER_LONIFY_LON_STRING_HPP

#include <string>

#include "config.hpp"
#include "lon_type.hpp"
#include "utility/stringifier.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    struct lon_string : public lon_type
    {
        lon_string(const std::string& value);

        enum_lon_type get_type() const override;

        friend std::string operator|(const lon_string& ls, const stringifier& s);

    private:
        std::string m_value;
    };

#ifdef PROJECT_NAMESPACE
}
#endif

#endif