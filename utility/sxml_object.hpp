#pragma once

#include "../xmlify/sxml_options.hpp"

#include <iosfwd>
#include <utility>
#include <string>

namespace SXML
{
    /*
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
    */

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
