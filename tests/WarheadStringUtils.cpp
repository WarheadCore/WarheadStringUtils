/*
 * This file is part of the WarheadStringUtils Project. See LICENSE file for Copyright information
 */

#include "catch2/catch.hpp"
#include "Warhead/Tokenizer.h"

TEST_CASE("Check count")
{
    std::string_view testTokens{ "1 2 3 4 5 6 7" };

    Warhead::String::Tokenizer tokenizer1{ testTokens, ' ' };
    Warhead::String::Tokenizer tokenizer2{ testTokens, ',' };

    REQUIRE(tokenizer1.GetCount() == 7);
    REQUIRE(tokenizer2.GetCount() == 1);
}

TEST_CASE("Check string tokens")
{
    std::string_view testTokens{ "1 2 3 4 5 6 7" };

    Warhead::String::Tokenizer tokenizer{ testTokens, ' ' };

    REQUIRE(tokenizer.GetCount() == 7);
    REQUIRE(tokenizer.Get(0) == "1");
    REQUIRE(tokenizer.Get(6) == "7");
    REQUIRE(tokenizer.Get(7).empty());
}

TEST_CASE("Check number tokens")
{
    std::string_view testTokens{ "1 2 3 4 5 6 7 a 7a" };

    Warhead::String::Tokenizer tokenizer{ testTokens, ' ' };

    REQUIRE(tokenizer.GetCount() == 9);
    REQUIRE(tokenizer.GetConvert<uint32_t>(0) == 1);
    REQUIRE(tokenizer.GetConvert<uint32_t>(6) == 7);
    REQUIRE(tokenizer.GetConvert<uint32_t>(7) == std::nullopt);
    REQUIRE(tokenizer.GetConvert<uint32_t>(8) == std::nullopt);
    REQUIRE(tokenizer.GetConvert<uint32_t>(9) == std::nullopt);
}

TEST_CASE("Check whitespace tokens")
{
    std::string_view testTokens{ "1 2 3 4 5 6 7          9        11" };

    Warhead::String::Tokenizer tokenizer{ testTokens, ' ', true };

    REQUIRE(tokenizer.GetCount() == 25);
    REQUIRE(tokenizer.GetConvert<uint32_t>(16) == 9);
    REQUIRE(tokenizer.GetConvert<uint32_t>(23) == std::nullopt);
    REQUIRE(tokenizer.Get(23).empty());
}

TEST_CASE("Check whitespace clean tokens")
{
    std::string_view testTokens{ "1, 2,3,4, 5, 6, 7,          9,        11," };

    Warhead::String::Tokenizer tokenizer{ testTokens, ',' };

    REQUIRE(tokenizer.GetCount() == 9);
    REQUIRE(tokenizer.GetConvert<uint32_t>(1) == std::nullopt);
    REQUIRE(tokenizer.GetConvert<uint32_t>(1, true) == 2);
    REQUIRE(tokenizer.GetConvert<uint32_t>(7) == std::nullopt);
    REQUIRE(tokenizer.GetConvert<uint32_t>(7, true) == 9);
}

TEST_CASE("Check uint64")
{
    REQUIRE(Warhead::String::Convert<uint64_t>("42") == 42);
    REQUIRE(Warhead::String::Convert<uint64_t>("42", 10) == 42);
    REQUIRE(Warhead::String::Convert<uint64_t>(" 42") == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint64_t>("tail42") == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint64_t>("42tail") == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint64_t>("-1", 0) == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint64_t>("ff", 16) == 0xff);
    REQUIRE(Warhead::String::Convert<uint64_t>("0xff") == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint64_t>("0xff", 0) == 0xff);
    REQUIRE(Warhead::String::Convert<uint64_t>("101010", 2) == 0b101010);
    REQUIRE(Warhead::String::Convert<uint64_t>("0b101010") == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint64_t>("0b101010", 0) == 0b101010);
    REQUIRE(Warhead::String::Convert<uint64_t>("5000000000") == 5000000000ULL);
    REQUIRE(Warhead::String::Convert<uint64_t>("100000000", 16) == 0x100000000ULL);
    REQUIRE(Warhead::String::Convert<uint64_t>("20000000000000000000") == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint64_t>("10000000000000000", 16) == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint64_t>("0x10000000000000000", 0) == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint64_t>("0xFFFFFFFFFFFFFFFF", 0) == 0xffffffffffffffffULL);
}

TEST_CASE("Check int64")
{
    REQUIRE(Warhead::String::Convert<int64_t>("-42") == -42);
    REQUIRE(Warhead::String::Convert<int64_t>("42") == 42);
    REQUIRE(Warhead::String::Convert<int64_t>("+42") == std::nullopt);
    REQUIRE(Warhead::String::Convert<int64_t>("--42") == std::nullopt);
    REQUIRE(Warhead::String::Convert<int64_t>("~42") == std::nullopt);
    REQUIRE(Warhead::String::Convert<int64_t>("42-") == std::nullopt);
    REQUIRE(Warhead::String::Convert<int64_t>("-ffff", 16) == -0xffff);
    REQUIRE(Warhead::String::Convert<int64_t>("ffffffff", 16) == 0xffffffff);
    REQUIRE(Warhead::String::Convert<int64_t>("7fffffff", 16) == 0x7fffffff);
    REQUIRE(Warhead::String::Convert<int64_t>("ffffffffffffffff", 16) == std::nullopt);
    REQUIRE(Warhead::String::Convert<int64_t>("7fffffffffffffff", 16) == 0x7fffffffffffffffLL);
    REQUIRE(Warhead::String::Convert<int64_t>("-8500000000000000", 16) == std::nullopt);
}

TEST_CASE("Check uint32")
{
    REQUIRE(Warhead::String::Convert<uint32_t>("42") == 42u);
    REQUIRE(Warhead::String::Convert<uint32_t>("42", 10) == 42u);
    REQUIRE(Warhead::String::Convert<uint32_t>(" 42") == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint32_t>("tail42") == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint32_t>("42tail") == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint32_t>("ff", 16) == 0xFFu);
    REQUIRE(Warhead::String::Convert<uint32_t>("0xff") == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint32_t>("0xff", 0) == 0xFFu);
    REQUIRE(Warhead::String::Convert<uint32_t>("101010", 2) == 0b101010u);
    REQUIRE(Warhead::String::Convert<uint32_t>("0b101010") == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint32_t>("0b101010", 0) == 0b101010u);
    REQUIRE(Warhead::String::Convert<uint32_t>("5000000000") == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint32_t>("100000000", 16) == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint32_t>("0x100000000", 0) == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint32_t>("0xffffffff", 0) == 0xFFFFFFFF);
}

TEST_CASE("Check int32")
{
    REQUIRE(Warhead::String::Convert<int32_t>("-42") == -42);
    REQUIRE(Warhead::String::Convert<int32_t>("42") == 42);
    REQUIRE(Warhead::String::Convert<int32_t>("+42") == std::nullopt);
    REQUIRE(Warhead::String::Convert<int32_t>("--42") == std::nullopt);
    REQUIRE(Warhead::String::Convert<int32_t>("~42") == std::nullopt);
    REQUIRE(Warhead::String::Convert<int32_t>("42-") == std::nullopt);
    REQUIRE(Warhead::String::Convert<int32_t>("-ffff", 16) == -0xffff);
    REQUIRE(Warhead::String::Convert<int32_t>("ffffffff", 16) == std::nullopt);
    REQUIRE(Warhead::String::Convert<int32_t>("7fffffff", 16) == 0x7fffffff);
}

TEST_CASE("Check uint16")
{
    REQUIRE(Warhead::String::Convert<uint16_t>("0x1ff", 0) == 0x1ff);
    REQUIRE(Warhead::String::Convert<uint16_t>("0x1ffff", 0) == std::nullopt);
    REQUIRE(Warhead::String::Convert<uint16_t>("-1", 0) == std::nullopt);
}

TEST_CASE("Check int16")
{
    REQUIRE(Warhead::String::Convert<int16_t>("0x1ff", 0) == 0x1ff);
    REQUIRE(Warhead::String::Convert<int16_t>("0xffff", 0) == std::nullopt);
    REQUIRE(Warhead::String::Convert<int16_t>("0x7fff", 0) == 0x7fff);
    REQUIRE(Warhead::String::Convert<int16_t>("-1", 0) == -1);
}

TEST_CASE("Check uint8")
{
    REQUIRE(Warhead::String::Convert<uint8_t>("0xff", 0) == 0xff);
    REQUIRE(Warhead::String::Convert<uint8_t>("0x1ff", 0) == std::nullopt);
}

TEST_CASE("Check int8")
{
    REQUIRE(Warhead::String::Convert<int8_t>("0xff", 0) == std::nullopt);
    REQUIRE(Warhead::String::Convert<int8_t>("0x7f", 0) == 0x7f);
    REQUIRE(Warhead::String::Convert<int8_t>("-7f", 16) == -0x7f);
}

TEST_CASE("Check bool")
{
    REQUIRE(Warhead::String::Convert<bool>("true") == true);
    REQUIRE(Warhead::String::Convert<bool>("false") == false);
    REQUIRE(Warhead::String::Convert<bool>("ture") == std::nullopt);
    REQUIRE(Warhead::String::Convert<bool>("1") == true);
    REQUIRE(Warhead::String::Convert<bool>("0") == false);
}

TEST_CASE("Check double")
{
    using namespace Catch::literals;
    REQUIRE(Warhead::String::Convert<double>("0.5") == 0.5);
    REQUIRE(Warhead::String::Convert<double>("0.1") == 0.1_a);
    REQUIRE(Warhead::String::Convert<double>("1.2.3") == std::nullopt);
    REQUIRE(Warhead::String::Convert<double>("1e+5") == 100000.0);
    REQUIRE(Warhead::String::Convert<double>("1e+3+5") == std::nullopt);
    REQUIRE(Warhead::String::Convert<double>("a1.5") == std::nullopt);
    REQUIRE(Warhead::String::Convert<double>("1.5tail") == std::nullopt);
    REQUIRE(Warhead::String::Convert<double>("0x0") == 0.0);
    REQUIRE(Warhead::String::Convert<double>("0x0", 16) == std::nullopt);
    REQUIRE(Warhead::String::Convert<double>("0", 16) == 0.0);
    REQUIRE(Warhead::String::Convert<double>("0x1.BC70A3D70A3D7p+6") == 0x1.BC70A3D70A3D7p+6);
    REQUIRE(Warhead::String::Convert<double>("0x1.BC70A3D70A3D7p+6", 10) == std::nullopt);
    REQUIRE(Warhead::String::Convert<double>("0x1.BC70A3D70A3D7p+6", 16) == std::nullopt);
    REQUIRE(Warhead::String::Convert<double>("1.BC70A3D70A3D7p+6", 16) == 0x1.BC70A3D70A3D7p+6);
    REQUIRE(Warhead::String::Convert<double>("0x1.2.3") == std::nullopt);
    REQUIRE(Warhead::String::Convert<double>("0x1.AAAp+1-3") == std::nullopt);
    REQUIRE(Warhead::String::Convert<double>("1.2.3", 16) == std::nullopt);
    REQUIRE(Warhead::String::Convert<double>("1.AAAp+1-3", 16) == std::nullopt);
}
