#ifndef ELF_CRAFTER_LONIFIER_HPP
#define ELF_CRAFTER_LONIFIER_HPP

#include <sstream>
#include <string>

#include "config.hpp"
#include "lon_array.hpp"
#include "lon_bytes.hpp"
#include "lon_object.hpp"
#include "lon_string.hpp"
#include "lon_type.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    /** `LON` is the acronym for `Log Object Notation` */

    struct lonifier
    {
        lonifier();

        template <typename T>
            requires std::is_fundamental_v<std::remove_cvref_t<T>>
        friend const lon_type* operator|(T&& t, const lonifier& l)
        {
            return new lon_string(std::to_string(std::forward<T>(t)));
        }

        template <typename T> friend const lon_type* operator|(T* t, const lonifier& l)
        {
            std::ostringstream oss;
            oss << std::hex << t;
            return new lon_string(oss.str());
        }

        friend const lon_type* operator|(const std::string& s, const lonifier& l);
    };

#ifdef PROJECT_NAMESPACE
}
#endif

#endif