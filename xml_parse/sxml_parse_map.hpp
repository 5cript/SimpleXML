#pragma once

#include "sxml_parse_core.hpp"

#include <map>

namespace SXML
{
    template <typename ValueT, typename CompareT = std::less <ValueT>, class AllocT = std::allocator <ValueT>>
    void xml_parse(std::map<std::string, ValueT, CompareT, AllocT>& value, NodeName const& name,
               PropertyTree const& object, XmlParseOptions const& options = {})
    {
        try
        {
            auto TEST = static_cast <std::string> (name);
            GET_CHILD(name, pt, (std::map <std::string, ValueT, CompareT, AllocT>()));
            for (auto const& i : pt)
            {
                ValueT temp;
                xml_parse(temp, name >> i.first, object, options);
                value[i.first] = temp;
            }
        }
        DEFAULT_CATCH({}, {})
    }
}
