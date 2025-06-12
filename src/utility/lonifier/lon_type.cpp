#include "utility/lonifier/lon_type.hpp"

#include "utility/lonifier/lon_array.hpp"
#include "utility/lonifier/lon_object.hpp"
#include "utility/lonifier/lon_string.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    const std::string operator|(const lon_type* l, const stringifier& s)
    {
        switch (l->get_type()) {
        case lon_type::enum_lon_type::STRING:
            return *dynamic_cast<const lon_string*>(l) | s;

        case lon_type::enum_lon_type::ARRAY:
            return *dynamic_cast<const lon_array*>(l) | s;

        case lon_type::enum_lon_type::OBJECT:
            return *dynamic_cast<const lon_object*>(l) | s;

        default:
            return "default case (should have been unreachable)";
        }
    }

#ifdef PROJECT_NAMESPACE
}
#endif