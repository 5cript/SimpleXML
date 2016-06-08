#pragma once

#include "../utility/sxml_iterator_traits.hpp"
#include "sxml_parse_core.hpp"

namespace SXML
{
    namespace Internal
    {
        template <typename T>
        struct emplacer;

        #define DECLARE_EMPLACER(CONTAINER, FUNCTION) \
        template <typename... List> \
        struct emplacer <CONTAINER <List...>> \
        { \
            template <typename T> \
            static void emplace(CONTAINER <List...>& container, T&& element) \
            { \
                container.FUNCTION(std::forward <T&&>(element)); \
            } \
        }

        DECLARE_EMPLACER(std::vector, emplace_back);
        DECLARE_EMPLACER(std::deque, emplace_back);
        DECLARE_EMPLACER(std::set, emplace);
        DECLARE_EMPLACER(std::list, emplace_back);
        DECLARE_EMPLACER(std::forward_list, emplace_back);

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
                GET_CHILD(parent, pt, {});

                auto range = pt.equal_range(name.getName());
                for (auto i = range.first; i != range.second; ++i)
                {
                    T temp;
                    xml_parse(temp, "", i->second, options);
                    emplacer<ContainerT<T, L...>>::emplace(value, std::move(temp));
                }
            }
            DEFAULT_CATCH({}, {})
            /*
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
            */
        }
    }
}
