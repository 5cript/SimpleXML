#pragma once

#include "sxml_core.hpp"

#include <boost/optional.hpp>

namespace SXML
{
    template <typename T>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, boost::optional <T> const& value, XmlifyOptions const& options = {})
    {
        if (value)
            xmlify(stream, name, value.get(), options);
        return stream;
    }
}
