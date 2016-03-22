#pragma once

#include "sxml_iterable.hpp"
#include <array>

namespace SXML
{
    template <typename T, std::size_t N>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::array <T, N> const& value, XmlifyOptions const& options = {})
    {
        return Internal::xmlify_generic_container(stream, name, value, options);
    }
}
