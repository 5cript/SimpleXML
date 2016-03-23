#pragma once

#include "sxml_core.hpp"

#include <unordered_set>

namespace SXML
{
    template <typename Key, typename Hash = std::hash <Key>, typename Pred = std::equal_to <Key>,
              typename Alloc = std::allocator <Key>>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::unordered_set <Key, Hash, Pred, Alloc> const& value, XmlifyOptions const& options = {})
    {
        return Internal::xmlify_generic_container(stream, name, value, options);
    }
}
