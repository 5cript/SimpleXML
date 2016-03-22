#pragma once

#include <iterator>
#include <type_traits>

namespace SXML
{
    template <typename T>
    struct is_random_access_iterator : std::is_same <
        typename std::iterator_traits<T>::iterator_category
        , std::random_access_iterator_tag>
    {};

    template <typename T>
    struct is_bidirectional_iterator : std::is_same <
        typename std::iterator_traits<T>::iterator_category
        , std::bidirectional_iterator_tag>
    {};

    template <typename T>
    struct is_forward_iterator : std::is_same <
        typename std::iterator_traits<T>::iterator_category
        , std::forward_iterator_tag>
    {};

    template <template <typename...> class ContainerT, typename... L>
    struct has_random_access_iterator : std::is_same <
        typename std::iterator_traits<typename ContainerT<L...>::iterator>::iterator_category
        , std::random_access_iterator_tag>
    {};

    template <template <typename...> class ContainerT, typename... L>
    struct has_bidirectional_iterator : std::is_same <
        typename std::iterator_traits<typename ContainerT<L...>::iterator>::iterator_category
        , std::bidirectional_iterator_tag>
    {};

    template <template <typename...> class ContainerT, typename... L>
    struct has_forward_iterator : std::is_same <
        typename std::iterator_traits<typename ContainerT<L...>::iterator>::iterator_category
        , std::forward_iterator_tag>
    {};
}
