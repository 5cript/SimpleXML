#pragma once

namespace SXML
{
    template <typename T>
    struct Attribute
    {
        using type = T;
        T value;

        operator T&()
        {
            return value;
        }

        operator T const&() const
        {
            return value;
        }
    };
}
