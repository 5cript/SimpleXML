#pragma once

#include "../xmlify/sxml_options.hpp"
#include "../xml_parse/sxml_parse_options.hpp"
#include "../utility/sxml_rename.hpp"

#include <iosfwd>
#include <utility>
#include <string>

namespace SXML
{
    namespace Internal
    {
        template< class... >
        using void_t = void;

        struct nonesuch {
            nonesuch() = delete;
            ~nonesuch() = delete;
            nonesuch(nonesuch const&) = delete;
            void operator=(nonesuch const&) = delete;
        };

        namespace experimental
        {
            namespace detail
            {
                template <class Default, class AlwaysVoid,
                          template<class...> class Op, class... Args>
                struct detector {
                    using value_t = std::false_type;
                    using type = Default;
                };

                template <class Default, template<class...> class Op, class... Args>
                struct detector<Default, void_t<Op<Args...>>, Op, Args...> {
                    // Note that std::void_t is a C++17 feature
                    using value_t = std::true_type;
                    using type = Op<Args...>;
                };

            } // namespace detail

            template <template<class...> class Op, class... Args>
            using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

            template <template<class...> class Op, class... Args>
            using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

            template <class Default, template<class...> class Op, class... Args>
            using detected_or = detail::detector<Default, void, Op, Args...>;

            template< template<class...> class Op, class... Args >
            constexpr bool is_detected_v = is_detected<Op, Args...>::value;

            template< class Default, template<class...> class Op, class... Args >
            using detected_or_t = typename detected_or<Default, Op, Args...>::type;

            template <class Expected, template<class...> class Op, class... Args>
            using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;

            template <class Expected, template<class...> class Op, class... Args>
            constexpr bool is_detected_exact_v = is_detected_exact<Expected, Op, Args...>::value;

            template <class To, template<class...> class Op, class... Args>
            using is_detected_convertible = std::is_convertible<detected_t<Op, Args...>, To>;

            template <class To, template<class...> class Op, class... Args>
            constexpr bool is_detected_convertible_v = is_detected_convertible<To, Op, Args...>::value;
        }

        template <typename T>
        using has_xmlify_1 = decltype(std::declval<T&>().xmlify(std::declval<std::ostream&>(),
                                                                std::declval<std::string const&>(),
                                                                std::declval<XmlifyOptions>()));

        template <typename T>
        using has_xmlify_2 = decltype(std::declval<T&>().xmlify(std::declval<std::ostream&>(),
                                                                std::declval<std::string const&>(),
                                                                std::declval<XmlifyOptions const&>()));

        template <typename T>
        using has_xml_parse_1 = decltype(std::declval<T&>().xml_parse(std::declval<NodeName const&>(),
                                                                    std::declval<PropertyTree const&>(),
                                                                    std::declval<XmlParseOptions const&>()));

        template <typename T>
        using has_xml_parse_2 = decltype(std::declval<T&>().xml_parse(std::declval<NodeName const&>(),
                                                                    std::declval<PropertyTree const&>(),
                                                                    std::declval<XmlParseOptions>()));

        #define SFINAE_HAS_XML_PARSE(T) Internal::experimental::is_detected_exact_v <void, Internal::has_xml_parse_1, T> || \
                                        Internal::experimental::is_detected_exact_v <void, Internal::has_xml_parse_2, T>

        #define SFINAE_HAS_XMLIFY(T) Internal::experimental::is_detected_exact_v <std::ostream&, Internal::has_xmlify_1, T> || \
                                     Internal::experimental::is_detected_exact_v <std::ostream&, Internal::has_xmlify_2, T>

        template <typename T>
        constexpr typename std::enable_if <std::is_class <T>::value, bool>::type isXmlObject2(T)
        {
            return SFINAE_HAS_XMLIFY(T);
        }

        template <typename T>
        constexpr typename std::enable_if <!std::is_class <T>::value, bool>::type isXmlObject2(T)
        {
            return false;
        }
    }
}
