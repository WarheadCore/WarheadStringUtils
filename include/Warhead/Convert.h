/*
 * This file is part of the WarheadStringUtils Project. See LICENSE file for Copyright information
 */

#ifndef WARHEAD_STRING_UTILS_H_
#define WARHEAD_STRING_UTILS_H_

#include "Algorithm.h"
#include <charconv>
#include <optional>
#include <string>

namespace Warhead::Impl::StringConvert
{
    template <typename T>
    struct dependant_false { static constexpr bool value = false; };

    template <typename T>
    constexpr bool dependant_false_v = dependant_false<T>::value;

    template <typename T, typename = void>
    struct ConvertImpl
    {
        static_assert(dependant_false_v<T>, "Unsupported type used for Convert");
    };

    template <>
    struct ConvertImpl<bool, void>
    {
        static std::optional<bool> Convert(std::string_view str)
        {
            if (str.empty())
                return {};

            if (String::IsAnyStringEqual(str, "1", "yes", "true"))
                return true;

            if (String::IsAnyStringEqual(str, "0", "no", "false"))
                return false;

            return {};
        }
    };

    template <typename T>
    struct ConvertImpl<T, std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, bool>>>
    {
        static std::optional<T> Convert(std::string_view str, int base = 10)
        {
            if (str.empty())
                return {};

            if (base == 0)
            {
                if (String::IsStringEqual(str.substr(0, 2), "0x"))
                {
                    base = 16;
                    str.remove_prefix(2);
                }
                else if (String::IsStringEqual(str.substr(0, 2), "0b"))
                {
                    base = 2;
                    str.remove_prefix(2);
                }
                else
                    base = 10;

                if (str.empty())
                    return {};
            }

            T result{};
            auto const startPos = str.data();
            auto const endPos = startPos + str.size();

            auto const [ptr, ec] { std::from_chars(startPos, endPos, result, base) };
            if (ec != std::errc() || ptr != endPos)
                return {};

            return result;
        }
    };

    template <typename T>
    struct ConvertImpl<T, std::enable_if_t<std::is_floating_point_v<T>>>
    {
        static std::optional<T> Convert(std::string_view str, std::chars_format fmt = std::chars_format())
        {
            if (str.empty())
                return {};

            if (fmt == std::chars_format())
            {
                if (String::IsStringEqual(str.substr(0, 2), "0x"))
                {
                    fmt = std::chars_format::hex;
                    str.remove_prefix(2);
                }
                else
                    fmt = std::chars_format::general;

                if (str.empty())
                    return {};
            }

            T result{};
            auto const startPos = str.data();
            auto const endPos = startPos + str.size();

            auto const [ptr, ec] { std::from_chars(startPos, endPos, result, fmt) };
            if (ec != std::errc() || ptr != endPos)
                return {};

            return result;
        }

        static std::optional<T> Convert(std::string_view str, int base)
        {
            if (str.empty())
                return {};

            if (base == 16)
                return Convert(str, std::chars_format::hex);
            else if (base == 10)
                return Convert(str, std::chars_format::general);

            return Convert(str, std::chars_format());
        }
    };
}

namespace Warhead::String
{
    template<typename T, typename... Args>
    std::optional<T> Convert(std::string_view str, Args&&... args)
    {
        return Warhead::Impl::StringConvert::ConvertImpl<T>::Convert(str, std::forward<Args>(args)...);
    }
}

#endif
