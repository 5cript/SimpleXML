#pragma once

#include "sxml_core.hpp"

#include <utility>

namespace SXML
{
    template <typename FirstT, typename SecondT>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::pair <FirstT, SecondT> const& value, XmlifyOptions const& options = {})
    {
        using namespace Internal;
        tag_start(stream, name, options);
        xmlify(stream, "first", value.first, options);
        xmlify(stream, "second", value.second, options);
        tag_end(stream, name, options);
        return stream;
    }
}
