#pragma once

#include "../utility/sxml_rename.hpp"

namespace SXML
{
    template <typename T, typename Name>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, Rename <T, Name> const& value, XmlifyOptions const& options = {})
    {
        auto const& actual = value.getValue();
        return SXML::xmlify(stream, Name::c_str, actual, options);
    }
}
