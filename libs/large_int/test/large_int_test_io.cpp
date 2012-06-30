// large_int_test_io.cpp - Boost.LargeInt Library test file ------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#include <ios> // For std::ios_base
#include <sstream> // For std::istringstream, std::ostringstream,
                   //     std::wistringstream, std::wostringstream
#include <iomanip> // For std::dec, std::oct, std::hex, std::uppercase
#include <boost/cstdint.hpp> // For int8_t, uint8_t
#include <boost/large_int.hpp>
#include <boost/large_int/io.hpp>

#define BOOST_TEST_MODULE boost_large_int_io
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( large_int_io )
{
    using boost::large_int::large_int;

    // Declare a signed 16bit integer type for testing
    typedef large_int<uint8_t, int8_t> test_int16_t;
    test_int16_t result_16;

    // Check stream input
    std::istringstream iss;
    BOOST_CHECK_EQUAL((iss.str("0"), iss >> result_16, result_16), 0);
    BOOST_CHECK_EQUAL((iss.str("1"), iss >> result_16, result_16), 1);
    BOOST_CHECK_EQUAL((iss.str("2"), iss >> result_16, result_16), 2);
    BOOST_CHECK_EQUAL((iss.str("+1"), iss >> result_16, result_16), +1);
    BOOST_CHECK_EQUAL((iss.str("-1"), iss >> result_16, result_16), -1);
    BOOST_CHECK_EQUAL((iss.str("77"), iss >> std::oct >> result_16, result_16), 077);
    BOOST_CHECK_EQUAL((iss.str("ab"), iss >> std::hex >> result_16, result_16), 0xab);
    BOOST_CHECK_EQUAL((iss.str("AB"), iss >> std::hex >> result_16, result_16), 0xab);
    BOOST_CHECK_EQUAL((iss.str("077"), iss >> result_16, result_16), 077);
    BOOST_CHECK_EQUAL((iss.str("0xa"), iss >> result_16, result_16), 0xa);
    BOOST_CHECK((iss.str(""), iss >> result_16, iss.fail()));
    iss.clear();

    // Check stream input with leading whitespace and the raising of exceptions
    BOOST_CHECK_EQUAL((iss.str("  12"), iss >> std::dec >> std::skipws >> result_16, result_16), 12);
    BOOST_CHECK((iss.str("  12"), iss >> std::dec >> std::noskipws >> result_16, iss.fail()));
    BOOST_CHECK_THROW((iss.clear(), iss.str("  12"), iss.exceptions(std::ios_base::failbit),
        iss >> std::dec >> std::noskipws >> result_16), std::ios_base::failure);
    BOOST_CHECK((iss.clear(), iss.exceptions(std::ios_base::goodbit), iss.str(""), iss >> result_16, iss.fail()));
    BOOST_CHECK_THROW((iss.clear(), iss.str(""), iss.exceptions(std::ios_base::failbit), iss >> result_16), std::ios_base::failure);

    // Check stream output
    std::ostringstream oss;
    BOOST_CHECK_EQUAL((result_16 = 0, oss.str(""), oss << result_16, oss.str()), "0");
    BOOST_CHECK_EQUAL((result_16 = 1, oss.str(""), oss << result_16, oss.str()), "1");
    BOOST_CHECK_EQUAL((result_16 = 2, oss.str(""), oss << result_16, oss.str()), "2");
    BOOST_CHECK_EQUAL((result_16 = 10, oss.str(""), oss << std::dec << result_16, oss.str()), "10");
    BOOST_CHECK_EQUAL((result_16 = 077, oss.str(""), oss << std::oct << result_16, oss.str()), "77");
    BOOST_CHECK_EQUAL((result_16 = 0xa, oss.str(""), oss << std::hex << result_16, oss.str()), "a");
    BOOST_CHECK_EQUAL((result_16 = 10, oss.str(""), oss << std::showbase << std::dec << result_16, oss.str()), "10");
    BOOST_CHECK_EQUAL((result_16 = 077, oss.str(""), oss << std::showbase << std::oct << result_16, oss.str()), "077");
    BOOST_CHECK_EQUAL((result_16 = 0xa, oss.str(""), oss << std::showbase << std::hex << result_16, oss.str()), "0xa");
    BOOST_CHECK_EQUAL((result_16 = 10, oss.str(""), oss << std::showpos << std::dec << result_16, oss.str()), "+10");
    BOOST_CHECK_EQUAL((result_16 = test_int16_t(-10), oss.str(""), oss << std::showpos << std::dec << result_16, oss.str()), "-10");
    BOOST_CHECK_EQUAL((result_16 = 0xab, oss.str(""), oss << std::showbase << std::uppercase << std::hex << result_16, oss.str()), "0XAB");

    // Check wide-character input support
    std::wistringstream wiss;
    BOOST_CHECK_EQUAL((wiss.str(L"0"), wiss >> result_16, result_16), 0);
    BOOST_CHECK_EQUAL((wiss.str(L"123"), wiss >> result_16, result_16), 123);
    BOOST_CHECK_EQUAL((wiss.str(L"456"), wiss >> result_16, result_16), 456);
    BOOST_CHECK_EQUAL((wiss.str(L"-789"), wiss >> result_16, result_16), -789);
    BOOST_CHECK_EQUAL((wiss.str(L"-285"), wiss >> result_16, result_16), -285);

    // Check wide-character output support
    std::wostringstream woss;
    BOOST_CHECK((result_16 = 0, woss.str(L""), woss << result_16, woss.str()) == L"0");
    BOOST_CHECK((result_16 = 123, woss.str(L""), woss << result_16, woss.str()) == L"123");
    BOOST_CHECK((result_16 = 456, woss.str(L""), woss << result_16, woss.str()) == L"456");
    BOOST_CHECK((result_16 = -789, woss.str(L""), woss << result_16, woss.str()) == L"-789");
    BOOST_CHECK((result_16 = -285, woss.str(L""), woss << result_16, woss.str()) == L"-285");
}
