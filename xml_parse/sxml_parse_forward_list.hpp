#pragma once

#include "sxml_parse_iterable.hpp"
#include <forward_list>

namespace SXML
{
    template <typename T>
    void xml_parse(std::forward_list <T>& value, NodeName const& name, PropertyTree const& tree, XmlParseOptions const& options = {})
    {
        Internal::xml_parse_generic_container(value, name, tree, options);
    }
}
