#ifndef ELF_PARSER_JSONIFY_JSON_STRING_HPP
#define ELF_PARSER_JSONIFY_JSON_STRING_HPP

#include <string>

#include "config.hpp"
#include "json_type.hpp"
#include "utility/stringifier.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    struct json_string : public json_type
    {
        json_string(const std::string& value);

        enum_json_type get_type() const override;

        friend std::string operator|(const json_string& js, const stringifier& s);

    private:
        std::string m_value;
    };

#ifdef PROJECT_NAMESPACE
}
#endif

#endif