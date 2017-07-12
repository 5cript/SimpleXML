#pragma once

#include <type_traits>
#include <cstdint>

namespace SXML
{
    template <typename T, T Value>
    using integral = std::integral_constant <T, Value>;

#define SXML_DECLARE_INTEGRAL(TYPE) \
    template <TYPE V> \
    using TYPE ## _ = SXML::integral <TYPE, V>

#define SXML_DECLARE_INTEGRAL_N(TYPE, NAME) \
    template <TYPE V> \
    using NAME ## _ = SXML::integral <TYPE, V>

    SXML_DECLARE_INTEGRAL(bool);
    SXML_DECLARE_INTEGRAL(int);
    SXML_DECLARE_INTEGRAL(long);
    SXML_DECLARE_INTEGRAL_N(long long, long_long);
    SXML_DECLARE_INTEGRAL(short);
    SXML_DECLARE_INTEGRAL(unsigned);

    SXML_DECLARE_INTEGRAL_N(unsigned int, unsigned_int);
    SXML_DECLARE_INTEGRAL_N(unsigned long, unsigned_long);
    SXML_DECLARE_INTEGRAL_N(unsigned long long, unsigned_long_long);
    SXML_DECLARE_INTEGRAL_N(unsigned short, unsigned_short);

    SXML_DECLARE_INTEGRAL(uint8_t);
    SXML_DECLARE_INTEGRAL(uint16_t);
    SXML_DECLARE_INTEGRAL(uint32_t);
    SXML_DECLARE_INTEGRAL(uint64_t);

    SXML_DECLARE_INTEGRAL(int8_t);
    SXML_DECLARE_INTEGRAL(int16_t);
    SXML_DECLARE_INTEGRAL(int32_t);
    SXML_DECLARE_INTEGRAL(int64_t);

    using true_ = bool_ <true>;
    using false_ = bool_ <false>;
}
