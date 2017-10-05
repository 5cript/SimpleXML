#pragma once

#include "sxml_parse_core.hpp"
#include "../utility/sxml_map_dummy.hpp"

#include <map>
#include <boost/lexical_cast.hpp>

namespace SXML
{
    template <typename ValueT, typename CompareT = std::less <ValueT>, class AllocT = std::allocator <ValueT>>
    void xml_parse(std::map <std::string, ValueT, CompareT, AllocT>& value, NodeName const& name,
                   PropertyTree const& object, XmlParseOptions const& options = {})
    {
        try
        {
            SXML_GET_CHILD(name, pt, (std::map <std::string, ValueT, CompareT, AllocT>()));
            for (auto const& i : pt)
            {
                ValueT temp;
                xml_parse(temp, name >> i.first, object, options);
                value[i.first] = temp;
            }
        }
        SXML_DEFAULT_CATCH({}, {})
    }

    template <typename KeyT, typename ValueT, typename CompareT = std::less <ValueT>, class AllocT = std::allocator <ValueT>,
              typename Convertible = typename std::enable_if <std::is_integral <KeyT>::value, void>::type>
    void xml_parse(std::map <KeyT, ValueT, CompareT, AllocT>& value, NodeName const& name,
                   PropertyTree const& object, XmlParseOptions const& options = {})
    {
        try
        {
            SXML_GET_CHILD(name, pt, (std::map <KeyT, ValueT, CompareT, AllocT>()));

            auto opt = object.tree.get_child_optional (static_cast <std::string> (name)); \
            if (opt)
            {

            }

            auto depluralized = name.getName();
            if (depluralized.back() == 's')
                depluralized.pop_back();
            auto range = pt.equal_range(static_cast <std::string> (depluralized));
            for (auto i = range.first; i != range.second; ++i)
            {
                Internal::map_dummy <KeyT, ValueT, false> temp;

                xml_parse(temp, "", i->second, options);
                value[temp.id] = temp.value;
            }
        }
        SXML_DEFAULT_CATCH({}, {})
    }
}
