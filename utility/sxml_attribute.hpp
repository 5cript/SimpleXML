#pragma once

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

        operator T()
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
}
