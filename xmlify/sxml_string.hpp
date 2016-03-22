#pragma once

#include "sxml_core.hpp"

namespace SXML
{
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::string const& value, XmlifyOptions const& options = {})
    {
        using namespace Internal;

        tag_start(stream, name, options);
        stream << value;
        tag_end(stream, value, options);

        return stream;
    }
}
