#pragma once

#include "sxml_core.hpp"

#include <boost/optional.hpp>

#ifdef __has_include                           // Check if __has_include is present
#if __has_include(<optional>)                // Check for a standard library
#include <optional>
#endif
#endif // defined(__has_include)

namespace SXML
{
    template <typename T>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, boost::optional <T> const& value, XmlifyOptions const& options = {})
    {
        if (value)
            return xmlify(stream, name, value.get(), options);
        return stream;
    }

#ifdef __has_include                           // Check if __has_include is present
#if __has_include(<optional>)
    template <typename T>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, std::optional <T> const& value, XmlifyOptions const& options = {})
    {
        if (value)
            return xmlify(stream, name, value.value(), options);
        return stream;
    }
#endif
#endif // __has_include
}
