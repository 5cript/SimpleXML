#pragma once

#include <type_traits>

namespace SXML
{
    namespace internal
    {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PACK
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename...>
        struct pack {};

        template <typename Pack>
        struct pack_size;

        template <typename... List>
        struct pack_size <pack <List...>> {
            enum {
                value = sizeof...(List)
            };
        };

        template <std::size_t Index, typename Pack>
        struct pack_element;

        template <typename Head, typename... Tail>
        struct pack_element <0, pack <Head, Tail...>> {
            using type = Head;
        };

        template <std::size_t Index, typename Head, typename... Tail>
        struct pack_element <Index, pack <Head, Tail...>>
            : pack_element <Index-1, pack <Tail...>>
        {
        };

        template <typename, typename>
        struct concat
        { };

        template <typename ... Ts, typename ... Us>
        struct concat <pack <Ts...>, pack <Us...>> {
            using type = pack <Ts..., Us...>;
        };

        template <typename T, typename U>
        using concat_t = typename concat <T, U>::type;

        template <typename Pack>
        struct pop_back
        { };

        template <>
        struct pop_back <pack <>> {
            using type = pack <>;
        };

        template <typename T>
        struct pop_back <pack <T>> {
            using type = pack <>;
        };

        template <typename T, typename ... List>
        struct pop_back <pack <T, List...>> {
            using type = concat_t <pack <T>, typename pop_back <pack <List...>>::type>;
        };

        template <typename Pack>
        using pop_back_t = typename pop_back <Pack>::type;

        template <typename Pack, template <typename...> class Function>
        struct apply {    };

        template <template <typename...> class Function, typename... List>
        struct apply <pack <List...>, Function> {
            using type = Function <List...>;
        };

        template <typename Pack, template <typename...> class Function>
        using apply_t = typename apply <Pack, Function>::type;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRIM
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename Pack, template <typename> class Predicate, bool Abort = false>
        struct trim_right {
            // Abort == false
            using type = typename std::conditional <Predicate<typename pack_element <pack_size <Pack>::value - 1, Pack>::type>::value,
                                                    typename trim_right <pop_back_t<Pack>, Predicate>::type,
                                                    Pack>::type;
        };

        template <typename Pack, template <typename> class Predicate>
        struct trim_right <Pack, Predicate, true> {
            using type = Pack;
        };

        template <template <typename> class Predicate>
        struct trim_right <pack <>, Predicate, false> {
            using type = pack <>;
        };

        template <typename Pack, template <typename> class Predicate>
        using trim_right_t = typename trim_right <Pack, Predicate>::type;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CEXPR_STRING
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <char C>
        using char_ = std::integral_constant <char, C>;

        template <typename... List>
        struct cexpr_string
        {
            using size_type = std::make_signed <std::size_t>::type;

            using type = pack <List...>;
            constexpr static const size_type size = sizeof...(List);
            constexpr static const size_type length = size;

            template <size_type N>
            struct at {
                static_assert(N < size, "Index out of bounds");

                constexpr static const char value = pack_element <N, cexpr_string::type>::type::value;
                using type = typename pack_element <N, cexpr_string::type>::type;
            };

            template <size_type N>
            using at_t = typename at <N>::type;

            constexpr static const char c_str[] = {
                List::value..., '\0'
            };

            constexpr static const size_type npos = -1;
        };

        template <typename... List>
        constexpr const char cexpr_string <List...>::c_str[];

        template <typename Char>
        struct is_zero {
            constexpr static const bool value = (Char::value == 0);
        };

        #define SXML_SPLIT_1(s, x)    SXML::internal::char_<( x < sizeof(s) ? s[x] : '\0' )>
        #define SXML_SPLIT_4(s, x)    SXML_SPLIT_1  (s, x), SXML_SPLIT_1  (s, x+1)  , SXML_SPLIT_1  (s, x+2)  , SXML_SPLIT_1  (s, x+3)
        #define SXML_SPLIT_16(s, x)   SXML_SPLIT_4  (s, x), SXML_SPLIT_4  (s, x+4)  , SXML_SPLIT_4  (s, x+8)  , SXML_SPLIT_4  (s, x+12)
        #define SXML_SPLIT_64(s, x)   SXML_SPLIT_16 (s, x), SXML_SPLIT_16 (s, x+16) , SXML_SPLIT_16 (s, x+32) , SXML_SPLIT_16 (s, x+48)
        #define SXML_SPLIT_256(s, x)  SXML_SPLIT_64 (s, x), SXML_SPLIT_64 (s, x+64) , SXML_SPLIT_64 (s, x+128) , SXML_SPLIT_64 (s, x+194)
        #define SXML_SPLIT_1024(s, x) SXML_SPLIT_256(s, x), SXML_SPLIT_256(s, x+256), SXML_SPLIT_256(s, x+512), SXML_SPLIT_256(s, x+768)

        #define SXML_STRING_IMPL(str, n) SXML::internal::apply_t <SXML::internal::trim_right_t <SXML::internal::pack <SXML_SPLIT_##n(str, 0)>, SXML::internal::is_zero>, SXML::internal::cexpr_string>

        #define SXML_SHORT_STRING(str) SXML_STRING_IMPL(str, 16)
        #define SXML_STRING(str) SXML_STRING_IMPL(str, 64)
        #define SXML_LONG_STRING(str) SXML_STRING_IMPL(str, 256) // HEAVY
        #define SXML_LONG_LONG_STRING(str) SXML_STRING_IMPL(str, 1024) // ULTRA HEAVY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }


}
