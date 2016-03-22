#pragma once

#include "sxml_core.hpp"
#include "iterator_traits.hpp"

namespace SXML
{
    namespace Internal
    {
        template <typename T, typename... L, template <typename...> class ContainerT>
        std::ostream& xmlify_generic_container(
            std::ostream& stream,
            std::string const& name,
            ContainerT <T, L...> const& value,
            XmlifyOptions options = {},
            typename std::enable_if <
                    has_random_access_iterator <ContainerT, L...>::value
                ||  has_bidirectional_iterator <ContainerT, L...>::value
                ||  has_forward_iterator <ContainerT, L...>::value
            >::type* = nullptr)
        {
            auto withoutTags = options.withoutTags();
            for (auto const& i : value)
            {
                tag_start(stream, name, options);
                xmlify(stream, name, i, withoutTags);
                tag_end(stream, name, options);
            }
            return stream;
        }
    }
}
