#pragma once

namespace SXML
{
    template <typename T>
    class Content
    {
    public:
        using type = T;
        T value;

        T& get()
        {
            return value;
        }

        operator T() const
        {
            return value;
        }

        Content& operator=(T const& t)
        {
            value = t;
            return *this;
        }

        Content& operator=(T&& t)
        {
            value = std::move(t);
            return *this;
        }

        Content(Content <T> const& other)
            : value(other.value)
        {
        }

        Content(Content <T>&& other)
            : value(std::move(other.value))
        {
        }

        Content(T const& other)
            : value(other)
        {
        }

        Content(T&& other)
            : value(std::move(other))
        {
        }

        Content()
            : value()
        {
        }
    };

    namespace Internal
    {
        template <typename U>
        struct isContent
        {
            constexpr static const bool value = false;
        };

        template <typename U>
        struct isContent <Content <U>>
        {
            constexpr static const bool value = true;
        };
    }
}
