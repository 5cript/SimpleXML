#pragma once

#include "sxml_core.hpp"
#include "sxml_iterable.hpp"

#include <set>

namespace SXML
{
    template <typename T, typename CompareT = std::less <T>, typename Alloc = std::allocator <T> >
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::set <T, CompareT, Alloc> const& value, XmlifyOptions const& options = {})
    {
        return Internal::xmlify_generic_container(stream, name, value, options);
    }
}
