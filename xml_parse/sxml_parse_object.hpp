#pragma once

#include "../utility/sxml_object.hpp"

namespace SXML
{
    template <typename T>
    typename std::enable_if <SFINAE_HAS_XML_PARSE(T), void>::type
    xml_parse(T& value, NodeName const& name, PropertyTree const& tree, XmlParseOptions const& options = {})
    {
        value.xml_parse(name, tree, options);
    }
}
