#pragma once

namespace SXML
{
    namespace Internal
    {
        template <typename...>
        struct emplacer;
    }
}

#define SXML_DECLARE_EMPLACER(CONTAINER, FUNCTION) \
namespace SXML \
{ \
    namespace Internal \
    { \
        template <typename... List> \
        struct emplacer <CONTAINER <List...>> \
        { \
            template <typename T> \
            static void emplace(CONTAINER <List...>& container, T&& element) \
            { \
                container.FUNCTION(std::forward <T&&>(element)); \
            } \
        }; \
    } \
}
