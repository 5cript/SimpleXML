#pragma once

#include "../utility/sxml_iterator_traits.hpp"
#include "sxml_parse_core.hpp"

namespace SXML
{
    namespace Internal
    {
        template <typename T, typename... L, template <typename...> class ContainerT>
        void xml_parse_generic_container(
            ContainerT <T, L...>& value,
            NodeName const& name,
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
                if (!options.stateMixing)
                    value.clear();

                auto parent = name.parent();
                SXML_GET_CHILD(parent, pt, {});

                auto range = pt.equal_range(name.getName());
                for (auto i = range.first; i != range.second; ++i)
                {
                    T temp;
                    xml_parse(temp, "", i->second, options);
                    emplacer<ContainerT<T, L...>>::emplace(value, std::move(temp));
                    //ContainerT<T, L...>.emplace(value, std::move(temp));
                }
            }
            SXML_DEFAULT_CATCH({}, {})
        }
    }
}
