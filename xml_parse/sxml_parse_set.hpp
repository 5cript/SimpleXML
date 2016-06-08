#pragma once

#include "sxml_parse_iterable.hpp"

#include <set>

namespace SXML
{
    template <typename T, typename CompareT = std::less <T>, typename Alloc = std::allocator <T> >
    void xml_parse(std::set <T, CompareT, Alloc>& value, NodeName const& name, PropertyTree const& tree, XmlParseOptions const& options = {})
    {
        Internal::xml_parse_generic_container(value, name, tree, options);
    }
}

