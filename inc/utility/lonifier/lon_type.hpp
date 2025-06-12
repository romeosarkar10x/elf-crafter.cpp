#ifndef ELF_CRAFTER_LON_TYPE_HPP
#define ELF_CRAFTER_LON_TYPE_HPP

#include "config.hpp"
#include "utility/stringifier.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    struct lon_type
    {
        enum struct enum_lon_type
        {
            ARRAY,
            OBJECT,
            STRING,
        };

        virtual enum_lon_type get_type() const = 0;

        friend const std::string operator|(const lon_type* l, const stringifier& s);
    };

#ifdef PROJECT_NAMESPACE
}
#endif

#endif