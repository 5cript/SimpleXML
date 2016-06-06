#pragma once

#include "sxml_iterable.hpp"
#include <list>

namespace SXML
{
    template <typename T, typename Alloc = std::allocator <T> >
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::list <T, Alloc> const& value, XmlifyOptions const& options = {})
    {
        return Internal::xmlify_generic_container(stream, name, value, options);
    }
}
