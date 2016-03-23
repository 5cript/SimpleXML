#pragma once

#include "sxml_core.hpp"

namespace SXML
{
    inline std::ostream& xmlify(std::ostream& stream, std::string const& name, std::string const& value, XmlifyOptions const& options = {})
    {
        using namespace Internal;

        if (!value.empty())
        {
            tag_start(stream, name, options);
            stream << value;
            tag_end(stream, name, options);
        }
        else
        {
            if (!options.noSpace)
                stream << '<' << name << " />";
            else
                stream << '<' << name << "/>";
        }

        return stream;
    }
}
