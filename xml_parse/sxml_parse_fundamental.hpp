#pragma once

#include "sxml_parse_core.hpp"
#include "../utility/sxml_char_traits.hpp"

#include <type_traits>

namespace SXML
{
    template <typename T,
              class = typename std::enable_if<  (std::is_arithmetic<T>::value && !std::is_same<T, char>::value && !std::is_same<T, wchar_t>::value)
                                              || std::is_enum<T>::value         >::type>
    void xml_parse(T& value, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options)
    {
        try
        {
            GET_VALUE(T, name, value, {});
        }
        DEFAULT_CATCH({}, {})
    }


    template <typename T>
    typename std::enable_if <Internal::is_char_type<T>::value>::type
    xml_parse(T& value, NodeName const& name, PropertyTree const& object, XmlParseOptions const& options)
    {
        try
        {
            std::basic_string <T> s;
            GET_VALUE(std::basic_string <T>, name, s, T{});

            if (!s.empty())
                value = s.front();
        }
        DEFAULT_CATCH({}, {})
    }
}
