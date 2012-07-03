// large_int_test_shift.cpp - Boost.LargeInt Library test file ---------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#include <boost/cstdint.hpp> // For int8_t, uint8_t
#include <boost/large_int.hpp>
#include <boost/large_int/io.hpp>

#define BOOST_TEST_MODULE boost_large_int_shift
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( large_int_shift )
{
    using boost::large_int::large_int_shift;
    using boost::large_int::large_int;

    // Declare signed and unsigned 16bit integers for testing
    typedef large_int<uint8_t, int8_t> test_int16_t;
    typedef large_int<uint8_t, uint8_t> test_uint16_t;

    // Check large_int_shift::left for built-in values
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::left(0), int16_t(0));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::left(1), int16_t(2));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::left(2), int16_t(4));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::left(-1), int16_t(0xfffe));
    BOOST_CHECK_EQUAL(large_int_shift<uint16_t>::left(-1), uint16_t(0xfffe));

    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::left(1, 0), int16_t(1));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::left(0, 2), int16_t(0));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::left(1, 2), int16_t(4));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::left(2, 2), int16_t(8));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::left(-1, 2), int16_t(0xfffc));
    BOOST_CHECK_EQUAL(large_int_shift<uint16_t>::left(-1, 2), uint16_t(0xfffc));

    // Check large_int_shift::right for built-in values
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::right(0), int16_t(0));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::right(1), int16_t(0));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::right(2), int16_t(1));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::right(-1), int16_t(0xffff));
    BOOST_CHECK_EQUAL(large_int_shift<uint16_t>::right(-1), uint16_t(0x7fff));

    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::right(1, 0), int16_t(1));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::right(0, 2), int16_t(0));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::right(2, 2), int16_t(0));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::right(4, 2), int16_t(1));
    BOOST_CHECK_EQUAL(large_int_shift<int16_t>::right(-1, 2), int16_t(0xffff)); // Preserves sign
    BOOST_CHECK_EQUAL(large_int_shift<uint16_t>::right(-1, 2), uint16_t(0x3fff)); // Does not preserve a sign

    // Check large_int_shift::left for large_int values
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::left(0), test_int16_t(0));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::left(1), test_int16_t(2));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::left(2), test_int16_t(4));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::left(-1), test_int16_t(0xfffe));
    BOOST_CHECK_EQUAL(large_int_shift<test_uint16_t>::left(-1), test_uint16_t(0xfffe));
    BOOST_CHECK_EQUAL(large_int_shift<test_uint16_t>::left(0x80), test_uint16_t(0x100));

    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::left(1, 0), test_int16_t(1));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::left(0, 2), test_int16_t(0));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::left(1, 2), test_int16_t(4));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::left(2, 2), test_int16_t(8));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::left(-1, 2), test_int16_t(0xfffc));
    BOOST_CHECK_EQUAL(large_int_shift<test_uint16_t>::left(-1, 2), test_uint16_t(0xfffc));
    BOOST_CHECK_EQUAL(large_int_shift<test_uint16_t>::left(-1, 16), test_uint16_t(0xffff)); // Due to: bits %= size
    BOOST_CHECK_EQUAL(large_int_shift<test_uint16_t>::left(-1, 17), test_uint16_t(0xfffe)); // Due to: bits %= size
    BOOST_CHECK_EQUAL(large_int_shift<test_uint16_t>::left(0x40, 3), test_uint16_t(0x200));

    // Check large_int_shift::right for large_int values
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::right(0), test_int16_t(0));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::right(1), test_int16_t(0));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::right(2), test_int16_t(1));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::right(-1), test_int16_t(0xffff));
    BOOST_CHECK_EQUAL(large_int_shift<test_uint16_t>::right(-1), test_uint16_t(0x7fff));
    BOOST_CHECK_EQUAL(large_int_shift<test_uint16_t>::right(0x100), test_uint16_t(0x80));

    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::right(1, 0), test_int16_t(1));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::right(0, 2), test_int16_t(0));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::right(2, 2), test_int16_t(0));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::right(4, 2), test_int16_t(1));
    BOOST_CHECK_EQUAL(large_int_shift<test_int16_t>::right(-1, 2), test_int16_t(0xffff)); // Preserves sign
    BOOST_CHECK_EQUAL(large_int_shift<test_uint16_t>::right(-1, 2), test_uint16_t(0x3fff)); // Does not preserve a sign
    BOOST_CHECK_EQUAL(large_int_shift<test_uint16_t>::right(-1, 16), test_uint16_t(0xffff)); // Due to: bits %= size
    BOOST_CHECK_EQUAL(large_int_shift<test_uint16_t>::right(-1, 17), test_uint16_t(0x7fff)); // Due to: bits %= size
    BOOST_CHECK_EQUAL(large_int_shift<test_uint16_t>::right(0x200, 3), test_uint16_t(0x40));
}
