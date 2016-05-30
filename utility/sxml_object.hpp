#pragma once

#include "../xmlify/sxml_options.hpp"

#include <iosfwd>
#include <utility>
#include <string>

namespace SXML
{
    namespace Internal
    {
        template <typename Type,
                   class = typename std::enable_if <std::is_class <Type>::value>::type>
        class isXmlObject
        {
            class yes { char m; };
            class no { yes m[2]; };

            struct BaseMixin
            {
                std::ostream& xmlify(std::ostream& stream, std::string const&, XmlifyOptions) const { return stream; }
            };
            struct Base : public Type, public BaseMixin {};

            template <typename T, T> class Helper {};

            template <typename U>
            static no deduce(U*, Helper <std::ostream& (BaseMixin::*)(std::ostream&, std::string const&, XmlifyOptions), &U::xmlify>* = nullptr);

            static yes deduce(...);

        public:
            static const bool value = sizeof(yes) == sizeof(deduce((Base*)(nullptr)));
        };

        template <typename T>
        constexpr typename std::enable_if <std::is_class <T>::value, bool>::type isXmlObject2(T)
        {
            return isXmlObject <T>::value;
        }

        template <typename T>
        constexpr typename std::enable_if <!std::is_class <T>::value, bool>::type isXmlObject2(T)
        {
            return false;
        }
    }
}
