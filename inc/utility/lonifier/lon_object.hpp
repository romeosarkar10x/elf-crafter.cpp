#ifndef ELF_CRAFTER_LONIFY_LON_OBJECT
#define ELF_CRAFTER_LONIFY_LON_OBJECT

#include <map>

#include "config.hpp"
#include "lon_type.hpp"
#include "utility/stringifier.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    struct lon_object : public lon_type
    {
        lon_object();

        const lon_type* get_key(const std::string& key) const;
        void            set_key(const std::string& key, const lon_type* value);

        const std::map<std::string, const lon_type*>& get_key_value_map() const;

        enum_lon_type get_type() const override;

        friend std::string operator|(const lon_object& lo, const stringifier& s);

    private:
        std::map<std::string, const lon_type*> m_data;
    };

#ifdef PROJECT_NAMESPACE
}
#endif

#endif