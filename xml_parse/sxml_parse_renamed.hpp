#pragma once

#include "../utility/sxml_rename.hpp"

namespace SXML
{
    template <typename T, typename Name>
    void xml_parse(SXML::Rename <T, Name>& value, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options)
    {
		auto actual = name.parent();
		actual += Name::c_str;
        return SXML::xml_parse(value.getValue(), actual, object, options);
    }
}
