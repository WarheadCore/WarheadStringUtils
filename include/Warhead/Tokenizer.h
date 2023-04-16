/*
 * This file is part of the WarheadStringUtils Project. See LICENSE file for Copyright information
 */

#ifndef WARHEAD_STRING_TOKENIZER_H_
#define WARHEAD_STRING_TOKENIZER_H_

#include "Convert.h"
#include <vector>

namespace Warhead::String
{
    template<typename T, typename Storage>
    struct TokenizerIterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        explicit TokenizerIterator(Storage* ptr, bool removeWhitespace = false) :
            _ptr(ptr), _removeWhitespace(removeWhitespace) { }

        std::optional<T> operator*()
        {
            return _ptr->template GetConvert<T>(_index, _removeWhitespace);
        }

        std::optional<T> operator->()
        {
            return _ptr->template GetConvert<T>(_index, _removeWhitespace);
        }

        TokenizerIterator& operator++()
        {
            if (!_ptr->IsExistIndex(++_index))
                _ptr = nullptr;

            return *this;
        }

        bool operator!=(const TokenizerIterator& right) { return _ptr != right._ptr; }

    private:
        Storage* _ptr{};
        difference_type _index{};
        bool _removeWhitespace{};
    };

    template<class iterator>
    class IteratorPair
    {
    public:
        constexpr IteratorPair() : _iterators() { }
        constexpr IteratorPair(iterator first, iterator second) : _iterators(first, second) { }
        constexpr IteratorPair(std::pair<iterator, iterator> iterators) : _iterators(iterators) { }

        constexpr iterator begin() const { return _iterators.first; }
        constexpr iterator end() const { return _iterators.second; }

    private:
        std::pair<iterator, iterator> _iterators;
    };

    class Tokenizer
    {
    public:
        Tokenizer(std::string_view str, char separator, bool keepEmpty = false);

        [[nodiscard]] std::size_t GetCount() const { return _tokens.size(); }
        [[nodiscard]] std::string_view Get(std::size_t index, bool removeWhitespace = false) const;

        auto begin() { return _tokens.begin(); }
        auto end() { return _tokens.end(); }

        template<class T>
        std::optional<T> GetConvert(std::size_t index, bool removeWhitespace = false) const
        {
            return Convert<T>(Get(index, removeWhitespace));
        }

        [[nodiscard]] bool IsExistIndex(std::size_t index) const { return index < _tokens.size(); }

        template<class T>
        IteratorPair<TokenizerIterator<T, Tokenizer>> Iterate(bool removeWhitespace = false)
        {
            return { TokenizerIterator<T, Tokenizer>(this, removeWhitespace), TokenizerIterator<T, Tokenizer>(nullptr) };
        }

    private:
        std::string_view _str;
        std::vector<std::string_view> _tokens;
        char _separator{};
        bool _keepEmpty{};
    };
}

#endif
