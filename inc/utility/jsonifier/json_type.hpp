#ifndef ELF_CRAFTER_JSON_TYPE_HPP
#define ELF_CRAFTER_JSON_TYPE_HPP

#include "config.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    struct json_type
    {
        enum struct enum_json_type
        {
            ARRAY,
            OBJECT,
            STRING,
        };

        virtual enum_json_type get_type() const = 0;
    };

#ifdef PROJECT_NAMESPACE
}
#endif

#endif