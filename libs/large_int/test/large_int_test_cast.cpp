// large_int_test_cast.cpp - Boost.LargeInt Library test file ----------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#include <boost/cstdint.hpp> // For int8_t, int16_t, uint8_t, uint16_t
#include <boost/large_int.hpp>
#include <boost/large_int/io.hpp>

#define BOOST_TEST_MODULE boost_large_int_cast
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( large_int_cast )
{
    using boost::large_int::large_int;
    using boost::large_int::large_int_cast;

    // Declare signed and unsigned 16 and 24bit integers for testing
    typedef large_int<uint8_t, int8_t> test_int16_t;
    typedef large_int<uint8_t, uint8_t> test_uint16_t;
    typedef large_int<test_uint16_t, int8_t> test_int24_t;
    typedef large_int<test_uint16_t, uint8_t> test_uint24_t;

    // Check large_int_cast for casting between primitive types
    // [8 & 16bit, signed -> signed]
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(int8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(int8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(int8_t(-1)), int8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(int8_t(-2)), int8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(int16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(int16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(int16_t(-1)), int8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(int16_t(-2)), int8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(int8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(int8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(int8_t(-1)), int8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(int8_t(-2)), int8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(int16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(int16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(int16_t(-1)), int16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(int16_t(-2)), int16_t(-2));

    // [8 & 16bit, unsigned -> signed]
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(uint8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(uint8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(uint8_t(-1)), int8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(uint8_t(-2)), int8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(uint16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(uint16_t(-1)), int8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(uint16_t(-2)), int8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(uint8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(uint8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(uint8_t(-1)), int16_t(uint8_t(-1)));
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(uint8_t(-2)), int16_t(uint8_t(-2)));
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(uint16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(uint16_t(-1)), int16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<int16_t>(uint16_t(-2)), int16_t(-2));

    // [8 & 16bit, signed -> unsigned]
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(int8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(int8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(int8_t(-1)), uint8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(int8_t(-2)), uint8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(int16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(int16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(int16_t(-1)), uint8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(int16_t(-2)), uint8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(int8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(int8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(int8_t(-1)), uint16_t(int8_t(-1)));
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(int8_t(-2)), uint16_t(int8_t(-2)));
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(int16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(int16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(int16_t(-1)), uint16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(int16_t(-2)), uint16_t(-2));

    // [8 & 16bit, unsigned -> unsigned]
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(uint8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(uint8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(uint8_t(-1)), uint8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(uint8_t(-2)), uint8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(uint16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(uint16_t(-1)), uint8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(uint16_t(-2)), uint8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(uint8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(uint8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(uint8_t(-1)), uint8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(uint8_t(-2)), uint8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(uint16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(uint16_t(-1)), uint16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<uint16_t>(uint16_t(-2)), uint16_t(-2));

    // Check large_int_cast for casting between large_ints and primivites
    // [8 & 16bit, signed -> signed]
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(int8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(int8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(int8_t(-1)), int8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(int8_t(-2)), int8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(test_int16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(test_int16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(test_int16_t(-1)), int8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(test_int16_t(-2)), int8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(int8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(int8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(int8_t(-1)), int8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(int8_t(-2)), int8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_int16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_int16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_int16_t(-1)), test_int16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_int16_t(-2)), test_int16_t(-2));

    // [8 & 16bit, unsigned -> signed]
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(uint8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(uint8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(uint8_t(-1)), int8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(uint8_t(-2)), int8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(test_uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(test_uint16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(test_uint16_t(-1)), int8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<int8_t>(test_uint16_t(-2)), int8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(uint8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(uint8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(uint8_t(-1)), test_int16_t(uint8_t(-1)));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(uint8_t(-2)), test_int16_t(uint8_t(-2)));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_uint16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_uint16_t(-1)), test_int16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_uint16_t(-2)), test_int16_t(-2));

    // [8 & 16bit, signed -> unsigned]
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(int8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(int8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(int8_t(-1)), uint8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(int8_t(-2)), uint8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(test_int16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(test_int16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(test_int16_t(-1)), uint8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(test_int16_t(-2)), uint8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(int8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(int8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(int8_t(-1)), test_uint16_t(int8_t(-1)));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(int8_t(-2)), test_uint16_t(int8_t(-2)));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_int16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_int16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_int16_t(-1)), test_uint16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_int16_t(-2)), test_uint16_t(-2));

    // [8 & 16bit, unsigned -> unsigned]
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(uint8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(uint8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(uint8_t(-1)), uint8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(uint8_t(-2)), uint8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(test_uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(test_uint16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(test_uint16_t(-1)), uint8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<uint8_t>(test_uint16_t(-2)), uint8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(uint8_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(uint8_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(uint8_t(-1)), uint8_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(uint8_t(-2)), uint8_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_uint16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_uint16_t(-1)), test_uint16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_uint16_t(-2)), test_uint16_t(-2));

    // Check large_int_cast for casting between large_ints
    // [16 & 24bit, signed -> signed]
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_int16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_int16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_int16_t(-1)), test_int16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_int16_t(-2)), test_int16_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_int24_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_int24_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_int24_t(-1)), test_int16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_int24_t(-2)), test_int16_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_int16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_int16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_int16_t(-1)), test_int16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_int16_t(-2)), test_int16_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_int24_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_int24_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_int24_t(-1)), test_int24_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_int24_t(-2)), test_int24_t(-2));

    // [16 & 24bit, unsigned -> signed]
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_uint16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_uint16_t(-1)), test_int16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_uint16_t(-2)), test_int16_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_uint24_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_uint24_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_uint24_t(-1)), test_int16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_int16_t>(test_uint24_t(-2)), test_int16_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_uint16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_uint16_t(-1)), test_int24_t(test_uint16_t(-1)));
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_uint16_t(-2)), test_int24_t(test_uint16_t(-2)));
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_uint24_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_uint24_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_uint24_t(-1)), test_int24_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_int24_t>(test_uint24_t(-2)), test_int24_t(-2));

    // [16 & 24bit, signed -> unsigned]
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_int16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_int16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_int16_t(-1)), test_uint16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_int16_t(-2)), test_uint16_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_int24_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_int24_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_int24_t(-1)), test_uint16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_int24_t(-2)), test_uint16_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_int16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_int16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_int16_t(-1)), test_uint24_t(test_int16_t(-1)));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_int16_t(-2)), test_uint24_t(test_int16_t(-2)));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_int24_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_int24_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_int24_t(-1)), test_uint24_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_int24_t(-2)), test_uint24_t(-2));

    // [16 & 24bit, unsigned -> unsigned]
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_uint16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_uint16_t(-1)), test_uint16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_uint16_t(-2)), test_uint16_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_uint24_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_uint24_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_uint24_t(-1)), test_uint16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint16_t>(test_uint24_t(-2)), test_uint16_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_uint16_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_uint16_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_uint16_t(-1)), test_uint16_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_uint16_t(-2)), test_uint16_t(-2));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_uint24_t(1)), 1);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_uint24_t(2)), 2);
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_uint24_t(-1)), test_uint24_t(-1));
    BOOST_CHECK_EQUAL(large_int_cast<test_uint24_t>(test_uint24_t(-2)), test_uint24_t(-2));
}
