#pragma once

#include <utility>

namespace SXML
{
    template <typename T>
    struct Attribute
    {
        using type = T;
        T value;

        T& get()
        {
            return value;
        }

        T get() const
        {
            return value;
        }

        operator T() const
        {
            return value;
        }

        Attribute& operator=(T const& t)
        {
            value = t;
            return *this;
        }

        Attribute& operator=(T&& t)
        {
            value = std::move(t);
            return *this;
        }

        Attribute& operator=(Attribute const&) = default;
        Attribute& operator=(Attribute&&) = default;

        Attribute(Attribute <T> const& other)
            : value(other.value)
        {
        }

        Attribute(Attribute <T>&& other)
            : value(std::move(other.value))
        {
        }

        Attribute(T const& other)
            : value(other)
        {
        }

        Attribute(T&& other)
            : value(std::move(other))
        {
        }

        Attribute()
            : value()
        {
        }
    };

    namespace Internal
    {
        template <typename U>
        struct isAttribute
        {
            constexpr static const bool value = false;
        };

        template <typename U>
        struct isAttribute <Attribute <U>>
        {
            constexpr static const bool value = true;
        };
    }
}
