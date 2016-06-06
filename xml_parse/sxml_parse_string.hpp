#pragma once

#include "sxml_parse_core.hpp"

namespace SXML
{
    void xml_parse(std::string& value, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options = {});
}
