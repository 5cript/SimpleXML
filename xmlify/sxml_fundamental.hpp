#pragma once

#include "sxml_core.hpp"

namespace SXML
{
    template <typename T,
              class = typename std::enable_if<  (std::is_arithmetic<T>::value && !std::is_same<T, char>::value && !std::is_same<T, wchar_t>::value)
                                              || std::is_enum<T>::value         >::type>
    std::ostream& xmlify(std::ostream& stream, std::string const& name, T value, XmlifyOptions const& options = {})
    {
        using namespace Internal;

        if (!options.inArray)
            tag_start(stream, name, options);

        stream << value;

        if (!options.inArray)
            tag_end(stream, name, options);

        return stream;
    }
}
