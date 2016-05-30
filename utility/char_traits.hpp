#pragma once

#include <type_traits>

namespace SXML
{
    namespace Internal
    {
        template <typename T>
        struct is_char_type : std::false_type {};

        #define SXML_DECLARE_CHAR_TYPE(T) \
        template <> \
        struct is_char_type <T> : std::true_type {}

        SXML_DECLARE_CHAR_TYPE(char);
        SXML_DECLARE_CHAR_TYPE(wchar_t);
        SXML_DECLARE_CHAR_TYPE(char16_t);
        SXML_DECLARE_CHAR_TYPE(char32_t);
    }
}
