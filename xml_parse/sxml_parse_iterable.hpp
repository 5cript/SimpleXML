#pragma once

#include "../utility/iterator_traits.hpp"
#include "sxml_parse_core.hpp"

namespace SXML
{
    namespace Internal
    {
        template <typename T, typename... L, template <typename...> class ContainerT>
        std::ostream& xml_parse_generic_container(
            ContainerT <T, L...>& value,
            std::string const& name,
            PropertyTree const& object,
            XmlParseOptions options = {},
            typename std::enable_if <
                    has_random_access_iterator <ContainerT, L...>::value
                ||  has_bidirectional_iterator <ContainerT, L...>::value
                ||  has_forward_iterator <ContainerT, L...>::value
            >::type* = nullptr)
        {
            try
            {
                GET_CHILD(name, pt, {});
                for (auto const& i : pt)
                {
                    T temp;
                    xml_parse(temp, "", i.second, options);
                    value.emplace_back(std::move(temp));
                }
            }
            DEFAULT_CATCH({}, {})
        }
    }
}
