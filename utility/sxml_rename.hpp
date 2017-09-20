#pragma once

#include "../xmlify/sxml_core.hpp"
#include "../xml_parse/sxml_parse_core.hpp"

#include "sxml_meta_util.hpp"

#include <string>
#include <utility>
#include <type_traits>

namespace SXML
{
    template <typename T, typename Name>
    class Rename
    {
    public:
        using type = T;
        using name = Name;

        operator type&()
        {
            return objectValue_;
        }

        operator type() const
        {
            return objectValue_;
        }

        type getValue() const
        {
            return objectValue_;
        }

        type& getValue()
        {
            return objectValue_;
        }

        void setValue(type const& objectValue) const
        {
            objectValue_ = objectValue;
        }

        Rename <T, Name>& operator=(type const& objectValue)
        {
            objectValue_ = objectValue;
            return *this;
        }

        Rename <T, Name>& operator=(type&& objectValue)
        {
            objectValue_ = objectValue;
            return *this;
        }

        template <typename OtherName>
        Rename <T, Name>& operator=(Rename <T, OtherName> const& other)
        {
            if (this == &other)
                return *this;

            objectValue_ = other.objectValue_;
            return *this;
        }

        template <typename OtherName>
        Rename <T, Name>& operator=(Rename <T, OtherName>&& other)
        {
            objectValue_ = other.objectValue_;
            return *this;
        }

        template <typename OtherName>
        Rename(Rename <T, OtherName> const& other)
            : objectValue_(other.objectValue_)
        {
        }

        template <typename OtherName>
        Rename(Rename <T, OtherName>&& other)
            : objectValue_(std::move(other.objectValue_))
        {
        }

        Rename(type objectValue)
            : objectValue_(std::move(objectValue))
        {
        }

        template <typename U = type>
        Rename(typename std::enable_if <std::is_default_constructible <U>::value>::type* = nullptr)
            : objectValue_()
        {

        }

        ~Rename() = default;

        constexpr static const char* getName()
        {
            return name::c_str;
        }

    private:
        type objectValue_;
    };

    template <typename T>
    struct is_renamed
    {
        enum {
            value = false
        };
    };

    template <typename T, typename Name>
    struct is_renamed <Rename <T, Name>>
    {
        enum {
            value = true
        };
    };
}
