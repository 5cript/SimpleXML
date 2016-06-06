#pragma once

#include "sxml_iterable.hpp"
#include <deque>

namespace SXML
{
    template <typename T, typename Alloc = std::allocator <T> >
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::deque <T, Alloc> const& value, XmlifyOptions const& options = {})
    {
        return Internal::xmlify_generic_container(stream, name, value, options);
    }
}
