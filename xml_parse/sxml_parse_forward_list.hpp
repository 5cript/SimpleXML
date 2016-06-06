#pragma once

#include "sxml_iterable.hpp"
#include <forward_list>

namespace SXML
{
    template <typename T, typename Alloc = std::allocator <T> >
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::forward_list <T, Alloc> const& value, XmlifyOptions const& options = {})
    {
        return Internal::xmlify_generic_container(stream, name, value, options);
    }
}
