/*
 * This file is part of the WarheadStringUtils Project. See LICENSE file for Copyright information
 */

#include "Warhead/Algorithm.h"
#include <cctype>

constexpr char CHAR_WHITESPACE = ' ';

bool Warhead::String::IsStringEqual(std::string_view a, std::string_view b)
{
    return std::equal(a.begin(), a.end(), b.begin(), b.end(), [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
}

std::string_view Warhead::String::TrimLeft(std::string_view str)
{
    while (!str.empty() && (str.front() == CHAR_WHITESPACE))
        str.remove_prefix(1);

    return str;
}

std::string_view Warhead::String::TrimRight(std::string_view str)
{
    while (!str.empty() && (str.back() == CHAR_WHITESPACE))
        str.remove_suffix(1);

    return str;
}

std::string_view Warhead::String::TrimAll(std::string_view str)
{
    while (!str.empty() && (str.front() == CHAR_WHITESPACE))
        str.remove_prefix(1);

    while (!str.empty() && (str.back() == CHAR_WHITESPACE))
        str.remove_suffix(1);

    return str;
}
