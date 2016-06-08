#pragma once

#include "sxml_parse_core.hpp"

#include <unordered_map>

namespace SXML
{
    template <typename ValueT, typename HashT = std::hash <std::string>, class PredT = std::equal_to <std::string>,
              typename AllocT = std::allocator <std::pair <const std::string, ValueT>>>
    void xml_parse(std::unordered_map<std::string, ValueT, HashT, PredT, AllocT>& value, NodeName const& name,
               PropertyTree const& object, XmlParseOptions const& options = {})
    {
        try
        {
            GET_CHILD(name, pt, (std::unordered_map <std::string, ValueT, HashT, PredT, AllocT>()));
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
