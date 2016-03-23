#pragma once

#include "sxml_core.hpp"

namespace SXML
{
    inline std::ostream& xmlify(std::ostream& stream, std::string const& name, std::string const& value, XmlifyOptions const& options = {})
    {
        using namespace Internal;

        //if (!options.inArray)
            tag_start(stream, name, options);

        stream << value;

        //if (!options.inArray)
            tag_end(stream, name, options);

        return stream;
    }
}
