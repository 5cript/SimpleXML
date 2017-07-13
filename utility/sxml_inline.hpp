#pragma once

#include <utility>

namespace SXML
{
    template <typename T>
    class Inline
    {
    public:
        using type = T;
        T value;

        T& get()
        {
            return value;
        }

        T const& get() const
        {
            return value;
        }

        operator T() const
        {
            return value;
        }

        Inline& operator=(T const& t)
        {
            value = t;
            return *this;
        }

        Inline& operator=(T&& t)
        {
            value = std::move(t);
            return *this;
        }

        Inline& operator=(Inline const&) = default;
        Inline& operator=(Inline&&) = default;

        Inline(Inline <T> const& other)
            : value(other.value)
        {
        }

        Inline(Inline <T>&& other)
            : value(std::move(other.value))
        {
        }

        Inline(T const& other)
            : value(other)
        {
        }

        Inline(T&& other)
            : value(std::move(other))
        {
        }

        Inline()
            : value()
        {
        }
    };

    namespace Internal
    {
        template <typename U>
        struct isInline
        {
            constexpr static const bool value = false;
        };

        template <typename U>
        struct isInline <Inline <U>>
        {
            constexpr static const bool value = true;
        };
    }
}
