#pragma once

#include "sxml_core.hpp"
#include "../utility/sxml_object.hpp"
#include "../utility/sxml_iterator_traits.hpp"

#include <iostream>

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
            auto inArrayOptions = options;
            inArrayOptions.inArray = true;
            for (auto const& i : value)
            {
                if (!isXmlObject2(i))
                    tag_start(stream, name, options);

                xmlify(stream, name, i, inArrayOptions);

                if (!isXmlObject2(i))
                    tag_end(stream, name, options);
            }
            return stream;
        }
    }
}
