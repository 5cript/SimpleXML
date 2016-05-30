#pragma once

#include "sxml_parse_core.hpp"
#include "sxml_parse_iterable.hpp"

#include <deque>

namespace SXML
{
    template <typename T>
    void xml_parse(std::deque <T>& value, std::string const& name, PropertyTree const& tree, XmlParseOptions const& options = {})
    {
        Internal::xml_parse_generic_container(value, name, tree, options);
    }
}
