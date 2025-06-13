#include "utility/lonifier/lonifier.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    lonifier::lonifier() {}

    const lon_type* operator|(const std::string& s, const lonifier& l)
    {
        return new lon_string(s);
    }

#ifdef PROJECT_NAMESPACE
}
#endif