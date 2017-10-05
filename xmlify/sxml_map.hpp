#pragma once

#include "sxml_core.hpp"
#include "../utility/sxml_map_dummy.hpp"

#include <map>

#include <boost/lexical_cast.hpp>

namespace SXML
{
    template <typename T, typename CompareT = std::less <T>, typename Alloc = std::allocator <std::pair <const std::string, T>>>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::map <std::string, T, CompareT, Alloc> const& value, XmlifyOptions const& options = {})
    {
        using namespace Internal;
        tag_start(stream, name, options);
        for (auto const& i : value)
        {
            xmlify(stream, i.first, i.second, options);
        }
        tag_end(stream, name, options);
        return stream;
    }

    template <typename KeyT, typename ValueT, typename CompareT = std::less <ValueT>, typename Alloc = std::allocator <std::pair <const std::string, ValueT>>,
              typename = typename std::enable_if <!std::is_same <KeyT, std::string>::value, void>::type>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::map <KeyT, ValueT, CompareT, Alloc> const& value, XmlifyOptions const& options = {})
    {
        using namespace Internal;
        tag_start(stream, name, options);
        auto depluralized = name;
        if (depluralized.back() == 's')
            depluralized.pop_back();
        for (auto const& i : value)
            xmlify(stream, depluralized, map_dummy <KeyT, ValueT, true>{i.first, i.second}, options);
        tag_end(stream, name, options);
        return stream;
    }
}
