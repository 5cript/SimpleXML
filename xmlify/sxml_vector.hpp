#pragma once

#include "sxml_iterable.hpp"
#include <vector>

namespace SXML
{
    template <typename T, typename Alloc = std::allocator <T> >
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::vector <T, Alloc> const& value, XmlifyOptions const& options = {})
    {
        return Internal::xmlify_generic_container(stream, name, value, options);
    }
}
