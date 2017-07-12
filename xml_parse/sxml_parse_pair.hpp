#pragma once

#include "sxml_parse_core.hpp"

namespace SXML
{
    template <typename FirstT, typename SecondT>
    void xml_parse(std::pair <FirstT, SecondT>& value, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options = {})
    {
        try
        {
            xml_parse(value.first, name >> "first", object, options);
            xml_parse(value.second, name >> "second", object, options);
        }
        SXML_DEFAULT_CATCH({}, {});
    }
}
