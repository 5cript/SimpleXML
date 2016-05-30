#pragma once

#include "sxml_parse_core.hpp"

namespace SXML
{
    template <typename T,
              class = typename std::enable_if<  (std::is_arithmetic<T>::value && !std::is_same<T, char>::value && !std::is_same<T, wchar_t>::value)
                                              || std::is_enum<T>::value         >::type>
    void xml_parse(T& value, std::string const& name, PropertyTree const& object, XmlParseOptions const& options)
    {
        try
        {
            GET_VALUE(T, name, value, {});
        }
        DEFAULT_CATCH({}, {})
    }
}
