#ifndef ELF_CRAFTER_LONIFIER_LON_BYTES_HPP
#define ELF_CRAFTER_LONIFIER_LON_BYTES_HPP

#include <config.hpp>
#include <memory>

#include <utility/stringifier.hpp>

#include "lon_type.hpp"

#ifdef PROJECT_NAMESPACE
namespace PROJECT_NAMESPACE
{
#endif

    struct lon_bytes : public lon_type
    {
        lon_bytes(const std::byte* bytes, std::size_t size);

        enum_lon_type get_type() const override;

        friend const std::string operator|(const lon_bytes& lb, const stringifier& s);

    private:
        std::unique_ptr<std::byte> m_data;
        std::size_t                m_size;
    };
#ifdef PROJECT_NAMESPACE
}
#endif

#endif