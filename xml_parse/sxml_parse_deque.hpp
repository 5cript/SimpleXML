#pragma once

#include <deque>
#include "sxml_parse_iterable_common.hpp"
SXML_DECLARE_EMPLACER(std::deque, emplace_back);

#include "sxml_parse_iterable.hpp"

namespace SXML
{
    template <typename T>
    void xml_parse(std::deque <T>& value, NodeName const& name, PropertyTree const& tree, XmlParseOptions const& options = {})
    {
        Internal::xml_parse_generic_container(value, name, tree, options);
    }
}
