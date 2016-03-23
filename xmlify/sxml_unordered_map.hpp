#pragma once

#include "sxml_core.hpp"

#include <unordered_map>

namespace SXML
{
    template <typename T, typename Hash = std::hash <std::string>,
              typename Pred = std::equal_to <std::string>, typename Alloc = std::allocator <std::pair <std::string const, T> > >
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::unordered_map <std::string, T, Hash, Pred, Alloc> const& value, XmlifyOptions const& options = {})
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
