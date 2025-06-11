#ifndef ELF_CRAFTER_STRINGIFIER_HPP
#define ELF_CRAFTER_STRINGIFIER_HPP

#include <string>

#include "config.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif
    struct stringifier
    {
        stringifier();

        template <typename T> friend const std::string operator|(T value, const stringifier& s)
        {
            return std::to_string(value);
        }

    private:
        static char s_buffer[4096u];
    };
#ifdef PROJECT_NAMESPACE
}
#endif

#endif