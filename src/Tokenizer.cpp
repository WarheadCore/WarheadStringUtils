/*
 * This file is part of the WarheadStringUtils Project. See LICENSE file for Copyright information
 */

#include "Warhead/Tokenizer.h"

Warhead::String::Tokenizer::Tokenizer(std::string_view str, char separator, bool keepEmpty /*= false*/) :
    _str(str), _separator(separator), _keepEmpty(keepEmpty)
{
    std::size_t startPos{};

    for (std::size_t endPos = _str.find(_separator); endPos != std::string_view::npos; endPos = _str.find(_separator, startPos))
    {
        if (_keepEmpty || startPos < endPos)
            _tokens.emplace_back(_str.substr(startPos, endPos - startPos));

        startPos = endPos + 1;
    }

    if (_keepEmpty || startPos < _str.length())
        _tokens.emplace_back(_str.substr(startPos));
}

std::string_view Warhead::String::Tokenizer::Get(std::size_t index, bool removeWhitespace /*= false*/) const
{
    if (index >= _tokens.size())
        return {};

    auto token = _tokens[index];
    return removeWhitespace ? TrimAll(token) : token;
}
