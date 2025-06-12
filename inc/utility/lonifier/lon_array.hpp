#ifndef ELF_CRAFTER_LONIFIER_LON_ARRAY_HPP
#define ELF_CRAFTER_LONIFIER_LON_ARRAY_HPP

#include <vector>

#include "config.hpp"
#include "lon_type.hpp"
#include "utility/stringifier.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    struct lon_array : public lon_type
    {
        lon_array();

        void push(lon_type* object);
        void pop();

        const std::vector<lon_type*>& get_values() const;

        enum_lon_type get_type() const override;

        friend std::string operator|(const lon_array& la, const stringifier& s);

    private:
        std::vector<lon_type*> m_data;
    };

#ifdef PROJECT_NAMESPACE
}
#endif

#endif