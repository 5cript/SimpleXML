#pragma once

#include "sxml_core.hpp"
#include <map>

namespace SXML
{
    template <typename T, typename CompareT = std::less <T>, typename Alloc = std::allocator <std::pair <const std::string, T>>>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::map <std::string, T, CompareT, Alloc> const& value, XmlifyOptions const& options = {})
    {
        using namespace Internal;
        tag_start(stream, name, options);
        for (auto const& i : value)
        {
            tag_start(stream, i.first, options);
            stream << i.second;
            tag_end(stream, i.first, options);
        }
        tag_end(stream, name, options);
        return stream;
    }
}
