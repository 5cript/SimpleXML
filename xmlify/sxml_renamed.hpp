#pragma once

#include "../utility/sxml_rename.hpp"

namespace SXML
{
    template <typename T, typename Name>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, Rename <T, Name> const& value, XmlifyOptions const& options = {})
    {
        return SXML::xmlify(stream, Name::c_str, value.getValue(), options);
    }
}
