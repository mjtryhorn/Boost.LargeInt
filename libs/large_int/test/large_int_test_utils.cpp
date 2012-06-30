// large_int_test_utils.cpp - Boost.LargeInt Library test file ---------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#include <string> // For std::string, std::wstring
#include <stdexcept> // For std::invalid_argument
#include <boost/cstdint.hpp> // For int8_t, int16_t, int32_t,
                             //     uint8_t, uint16_t, uint32_t
#include <boost/large_int.hpp>
#include <boost/large_int/io.hpp>

#define BOOST_TEST_MODULE boost_large_int_utils
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( large_int_utils )
{
    using boost::large_int::large_int;
    using boost::large_int::abs;
    using boost::large_int::make_large_int;

    // Declare signed and unsigned 16bit and 32bit integers for testing
    typedef large_int<uint8_t, int8_t> test_int16_t;
    typedef large_int<uint8_t, uint8_t> test_uint16_t;
    typedef large_int<test_uint16_t, test_int16_t> test_int32_t;
    typedef large_int<test_uint16_t, test_uint16_t> test_uint32_t;

    test_int16_t result_16;
    const std::string test_num_str("123");
    const std::wstring test_wnum_str(L"456");
    const std::string test_base2_str("11001010");
    const std::string test_base3_str("11002012");

    // Check 'abs' for large_ints
    BOOST_CHECK_EQUAL(abs(test_int16_t(0)), 0);
    BOOST_CHECK_EQUAL(abs(test_int16_t(1)), 1);
    BOOST_CHECK_EQUAL(abs(test_int16_t(-1)), 1);
    BOOST_CHECK_EQUAL(abs(test_uint16_t(0)), 0);
    BOOST_CHECK_EQUAL(abs(test_uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(abs(test_uint16_t(-1)), uint16_t(-1));

    // Check make_large_int
    // [for positive, negative, decimal, octal and hexadecimal C-string values]
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("0"), 0);
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("1"), 1);
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("2"), 2);
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("+1"), 1);
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("+2"), 2);
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("-1"), -1);
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("-2"), -2);
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>(L"-30"), -30);
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("067"), int16_t(067));
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("077"), int16_t(077));
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("0xAB"), int16_t(0xab));
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("0xefff"), int16_t(0xefff));
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("0xffff"), int16_t(0xffff));
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("0x1ffff"), int16_t(0xffff));
    BOOST_CHECK_EQUAL(make_large_int<test_int16_t>("0XAB"), int16_t(0XAB));
    BOOST_CHECK_EQUAL(make_large_int<test_int32_t>("-1"), int32_t(-1));
    BOOST_CHECK_EQUAL(make_large_int<test_uint16_t>("-1"), uint16_t(-1));
    BOOST_CHECK_EQUAL(make_large_int<test_uint32_t>("-1"), uint32_t(-1));

    // [check make_large_int for an unspecified base value]
    BOOST_CHECK_EQUAL((make_large_int<test_int16_t>(
        test_num_str.begin(), test_num_str.end())), int16_t(123));
    BOOST_CHECK_EQUAL((make_large_int<test_int16_t>(
        test_wnum_str.begin(), test_wnum_str.end())), int16_t(456));
    BOOST_CHECK_EQUAL((make_large_int<test_int16_t>(
        test_num_str.begin(), test_num_str.end(), 0)), int16_t(123));
    BOOST_CHECK_EQUAL((make_large_int<test_int16_t>(
        test_wnum_str.begin(), test_wnum_str.end(), 0)), int16_t(456));
    BOOST_CHECK(make_large_int(test_num_str.begin(),
        test_num_str.end(), 0, result_16) == test_num_str.end());
    BOOST_CHECK_EQUAL((make_large_int(test_num_str.begin(),
        test_num_str.end(), 0, result_16), result_16), int16_t(123));

    // [check make_large_int for decimal input (base 10)]
    BOOST_CHECK_EQUAL((make_large_int<test_int16_t>(
        test_num_str.begin(), test_num_str.end(), 10)), int16_t(123));
    BOOST_CHECK_EQUAL((make_large_int<test_int16_t>(
        test_wnum_str.begin(), test_wnum_str.end(), 10)), int16_t(456));
    BOOST_CHECK(make_large_int(test_num_str.begin(),
        test_num_str.end(), 10, result_16) == test_num_str.end());
    BOOST_CHECK_EQUAL((make_large_int(test_num_str.begin(),
        test_num_str.end(), 10, result_16), result_16), int16_t(123));

    // [check make_large_int for octal input (base 8)]
    BOOST_CHECK_EQUAL((make_large_int<test_int16_t>(
        test_num_str.begin(), test_num_str.end(), 8)), int16_t(0123));
    BOOST_CHECK_EQUAL((make_large_int<test_int16_t>(
        test_wnum_str.begin(), test_wnum_str.end(), 8)), int16_t(0456));
    BOOST_CHECK(make_large_int(test_num_str.begin(),
        test_num_str.end(), 8, result_16) == test_num_str.end());
    BOOST_CHECK_EQUAL((make_large_int(test_num_str.begin(),
        test_num_str.end(), 8, result_16), result_16), int16_t(0123));

    // [check make_large_int for hexadecimal input (base 16)]
    BOOST_CHECK_EQUAL((make_large_int<test_int16_t>(
        test_num_str.begin(), test_num_str.end(), 16)), int16_t(0x123));
    BOOST_CHECK_EQUAL((make_large_int<test_int16_t>(
        test_wnum_str.begin(), test_wnum_str.end(), 16)), int16_t(0x456));
    BOOST_CHECK(make_large_int(test_num_str.begin(),
        test_num_str.end(), 16, result_16) == test_num_str.end());
    BOOST_CHECK_EQUAL((make_large_int(test_num_str.begin(),
        test_num_str.end(), 16, result_16), result_16), int16_t(0x123));

    // [check make_large_int for input of a non-standard base (binary, ternary)]
    BOOST_CHECK_EQUAL((make_large_int(test_base2_str.begin(),
        test_base2_str.end(), 2, result_16), result_16), int16_t(0xca));
    BOOST_CHECK_EQUAL((make_large_int(test_base3_str.begin(),
        test_base3_str.end(), 3, result_16), result_16), int16_t(0xb9f));

    // [check make_large_int for invalid inputs]
    BOOST_CHECK_THROW(make_large_int<test_int16_t>(""), std::invalid_argument);
    BOOST_CHECK_THROW(make_large_int<test_int16_t>("a"), std::invalid_argument);
    BOOST_CHECK_THROW(make_large_int<test_int16_t>("0a"), std::invalid_argument);
    BOOST_CHECK_THROW(make_large_int<test_int16_t>("0x"), std::invalid_argument);
    BOOST_CHECK_THROW(make_large_int<test_int16_t>("0xg"), std::invalid_argument);
    BOOST_CHECK_THROW(make_large_int<test_int16_t>("+"), std::invalid_argument);
    BOOST_CHECK_THROW(make_large_int<test_int16_t>("-"), std::invalid_argument);
}

