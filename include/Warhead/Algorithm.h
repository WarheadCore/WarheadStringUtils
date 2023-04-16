/*
 * This file is part of the WarheadStringUtils Project. See LICENSE file for Copyright information
 */

#ifndef WARHEAD_STRING_ALGORITHM_H_
#define WARHEAD_STRING_ALGORITHM_H_

#include <string_view>

namespace Warhead::String
{
    bool IsStringEqual(std::string_view a, std::string_view b);

    template <typename... Args>
    inline bool IsAnyStringEqual(std::string_view str, Args... args)
    {
        for (auto right : { args... })
            if (IsStringEqual(str, right))
                return true;

        return false;
    }

    std::string_view TrimLeft(std::string_view str);
    std::string_view TrimRight(std::string_view str);
    std::string_view TrimAll(std::string_view str);
}

#endif
