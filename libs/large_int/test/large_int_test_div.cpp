// large_int_test_div.cpp - Boost.LargeInt Library test file -----------------

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

#define BOOST_TEST_MODULE boost_large_int_div
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( large_int_div )
{
    using boost::large_int::large_int;
    using boost::large_int::large_int_div_t;
    using boost::large_int::div;

    // Declare signed and unsigned 16 and 24bit integers for testing
    typedef large_int<uint8_t, int8_t> test_int16_t;
    typedef large_int<uint8_t, uint8_t> test_uint16_t;
    typedef large_int<test_uint16_t, int8_t> test_int24_t;
    typedef large_int<test_uint16_t, uint8_t> test_uint24_t;

    // Test large_int_div_t constructor
    BOOST_CHECK_EQUAL(large_int_div_t<test_int16_t>().quot, test_int16_t(0));
    BOOST_CHECK_EQUAL(large_int_div_t<test_int16_t>().rem, test_int16_t(0));
    BOOST_CHECK_EQUAL(large_int_div_t<test_int16_t>(test_int16_t(1)).quot, test_int16_t(1));
    BOOST_CHECK_EQUAL(large_int_div_t<test_int16_t>(test_int16_t(1)).rem, test_int16_t(0));
    BOOST_CHECK_EQUAL(large_int_div_t<test_int16_t>(test_int16_t(2), test_int16_t(3)).quot, test_int16_t(2));
    BOOST_CHECK_EQUAL(large_int_div_t<test_int16_t>(test_int16_t(2), test_int16_t(3)).rem, test_int16_t(3));

    // Test div
    // [16bit, signed]
    BOOST_CHECK_EQUAL(div(test_int16_t(0), test_int16_t(1)).quot, int16_t(0) / int16_t(1));
    BOOST_CHECK_EQUAL(div(test_int16_t(0), test_int16_t(1)).rem, int16_t(0) % int16_t(1));
    BOOST_CHECK_EQUAL(div(test_int16_t(8), test_int16_t(3)).quot, int16_t(8) / int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(8), test_int16_t(3)).rem, int16_t(8) % int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(9), test_int16_t(3)).quot, int16_t(9) / int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(9), test_int16_t(3)).rem, int16_t(9) % int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(10), test_int16_t(3)).quot, int16_t(10) / int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(10), test_int16_t(3)).rem, int16_t(10) % int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(11), test_int16_t(3)).quot, int16_t(11) / int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(11), test_int16_t(3)).rem, int16_t(11) % int16_t(3));

    BOOST_CHECK_EQUAL(div(test_int16_t(0), test_int16_t(-1)).quot, int16_t(0) / int16_t(-1));
    BOOST_CHECK_EQUAL(div(test_int16_t(0), test_int16_t(-1)).rem, int16_t(0) % int16_t(-1));
    BOOST_CHECK_EQUAL(div(test_int16_t(8), test_int16_t(-3)).quot, int16_t(8) / int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(8), test_int16_t(-3)).rem, int16_t(8) % int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(9), test_int16_t(-3)).quot, int16_t(9) / int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(9), test_int16_t(-3)).rem, int16_t(9) % int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(10), test_int16_t(-3)).quot, int16_t(10) / int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(10), test_int16_t(-3)).rem, int16_t(10) % int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(11), test_int16_t(-3)).quot, int16_t(11) / int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(11), test_int16_t(-3)).rem, int16_t(11) % int16_t(-3));

    BOOST_CHECK_EQUAL(div(test_int16_t(-8), test_int16_t(3)).quot, int16_t(-8) / int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-8), test_int16_t(3)).rem, int16_t(-8) % int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-9), test_int16_t(3)).quot, int16_t(-9) / int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-9), test_int16_t(3)).rem, int16_t(-9) % int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-10), test_int16_t(3)).quot, int16_t(-10) / int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-10), test_int16_t(3)).rem, int16_t(-10) % int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-11), test_int16_t(3)).quot, int16_t(-11) / int16_t(3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-11), test_int16_t(3)).rem, int16_t(-11) % int16_t(3));

    BOOST_CHECK_EQUAL(div(test_int16_t(-8), test_int16_t(-3)).quot, int16_t(-8) / int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-8), test_int16_t(-3)).rem, int16_t(-8) % int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-9), test_int16_t(-3)).quot, int16_t(-9) / int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-9), test_int16_t(-3)).rem, int16_t(-9) % int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-10), test_int16_t(-3)).quot, int16_t(-10) / int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-10), test_int16_t(-3)).rem, int16_t(-10) % int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-11), test_int16_t(-3)).quot, int16_t(-11) / int16_t(-3));
    BOOST_CHECK_EQUAL(div(test_int16_t(-11), test_int16_t(-3)).rem, int16_t(-11) % int16_t(-3));

    BOOST_CHECK_EQUAL(div(test_int16_t(0x7fff), test_int16_t(0x7fff)).quot, int16_t(0x7fff) / int16_t(0x7fff));
    BOOST_CHECK_EQUAL(div(test_int16_t(0x7fff), test_int16_t(0x7fff)).rem, int16_t(0x7fff) % int16_t(0x7fff));
    BOOST_CHECK_EQUAL(div(test_int16_t(0x7fff), test_int16_t(0xffff)).quot, int16_t(0x7fff) / int16_t(0xffff));
    BOOST_CHECK_EQUAL(div(test_int16_t(0x7fff), test_int16_t(0xffff)).rem, int16_t(0x7fff) % int16_t(0xffff));
    BOOST_CHECK_EQUAL(div(test_int16_t(0xffff), test_int16_t(0x7fff)).quot, int16_t(0xffff) / int16_t(0x7fff));
    BOOST_CHECK_EQUAL(div(test_int16_t(0xffff), test_int16_t(0x7fff)).rem, int16_t(0xffff) % int16_t(0x7fff));
    BOOST_CHECK_EQUAL(div(test_int16_t(0xffff), test_int16_t(0xffff)).quot, int16_t(0xffff) / int16_t(0xffff));
    BOOST_CHECK_EQUAL(div(test_int16_t(0xffff), test_int16_t(0xffff)).rem, int16_t(0xffff) % int16_t(0xffff));

    // [16bit, unsigned]
    BOOST_CHECK_EQUAL(div(test_uint16_t(0), test_uint16_t(1)).quot, uint16_t(0) / uint16_t(1));
    BOOST_CHECK_EQUAL(div(test_uint16_t(0), test_uint16_t(1)).rem, uint16_t(0) % uint16_t(1));
    BOOST_CHECK_EQUAL(div(test_uint16_t(8), test_uint16_t(3)).quot, uint16_t(8) / uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(8), test_uint16_t(3)).rem, uint16_t(8) % uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(9), test_uint16_t(3)).quot, uint16_t(9) / uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(9), test_uint16_t(3)).rem, uint16_t(9) % uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(10), test_uint16_t(3)).quot, uint16_t(10) / uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(10), test_uint16_t(3)).rem, uint16_t(10) % uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(11), test_uint16_t(3)).quot, uint16_t(11) / uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(11), test_uint16_t(3)).rem, uint16_t(11) % uint16_t(3));

    BOOST_CHECK_EQUAL(div(test_uint16_t(0), test_uint16_t(-1)).quot, uint16_t(0) / uint16_t(-1));
    BOOST_CHECK_EQUAL(div(test_uint16_t(0), test_uint16_t(-1)).rem, uint16_t(0) % uint16_t(-1));
    BOOST_CHECK_EQUAL(div(test_uint16_t(8), test_uint16_t(-3)).quot, uint16_t(8) / uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(8), test_uint16_t(-3)).rem, uint16_t(8) % uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(9), test_uint16_t(-3)).quot, uint16_t(9) / uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(9), test_uint16_t(-3)).rem, uint16_t(9) % uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(10), test_uint16_t(-3)).quot, uint16_t(10) / uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(10), test_uint16_t(-3)).rem, uint16_t(10) % uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(11), test_uint16_t(-3)).quot, uint16_t(11) / uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(11), test_uint16_t(-3)).rem, uint16_t(11) % uint16_t(-3));

    BOOST_CHECK_EQUAL(div(test_uint16_t(-8), test_uint16_t(3)).quot, uint16_t(-8) / uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-8), test_uint16_t(3)).rem, uint16_t(-8) % uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-9), test_uint16_t(3)).quot, uint16_t(-9) / uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-9), test_uint16_t(3)).rem, uint16_t(-9) % uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-10), test_uint16_t(3)).quot, uint16_t(-10) / uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-10), test_uint16_t(3)).rem, uint16_t(-10) % uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-11), test_uint16_t(3)).quot, uint16_t(-11) / uint16_t(3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-11), test_uint16_t(3)).rem, uint16_t(-11) % uint16_t(3));

    BOOST_CHECK_EQUAL(div(test_uint16_t(-8), test_uint16_t(-3)).quot, uint16_t(-8) / uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-8), test_uint16_t(-3)).rem, uint16_t(-8) % uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-9), test_uint16_t(-3)).quot, uint16_t(-9) / uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-9), test_uint16_t(-3)).rem, uint16_t(-9) % uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-10), test_uint16_t(-3)).quot, uint16_t(-10) / uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-10), test_uint16_t(-3)).rem, uint16_t(-10) % uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-11), test_uint16_t(-3)).quot, uint16_t(-11) / uint16_t(-3));
    BOOST_CHECK_EQUAL(div(test_uint16_t(-11), test_uint16_t(-3)).rem, uint16_t(-11) % uint16_t(-3));

    BOOST_CHECK_EQUAL(div(test_uint16_t(0x7fff), test_uint16_t(0x7fff)).quot, uint16_t(0x7fff) / uint16_t(0x7fff));
    BOOST_CHECK_EQUAL(div(test_uint16_t(0x7fff), test_uint16_t(0x7fff)).rem, uint16_t(0x7fff) % uint16_t(0x7fff));
    BOOST_CHECK_EQUAL(div(test_uint16_t(0x7fff), test_uint16_t(0xffff)).quot, uint16_t(0x7fff) / uint16_t(0xffff));
    BOOST_CHECK_EQUAL(div(test_uint16_t(0x7fff), test_uint16_t(0xffff)).rem, uint16_t(0x7fff) % uint16_t(0xffff));
    BOOST_CHECK_EQUAL(div(test_uint16_t(0xffff), test_uint16_t(0x7fff)).quot, uint16_t(0xffff) / uint16_t(0x7fff));
    BOOST_CHECK_EQUAL(div(test_uint16_t(0xffff), test_uint16_t(0x7fff)).rem, uint16_t(0xffff) % uint16_t(0x7fff));
    BOOST_CHECK_EQUAL(div(test_uint16_t(0xffff), test_uint16_t(0xffff)).quot, uint16_t(0xffff) / uint16_t(0xffff));
    BOOST_CHECK_EQUAL(div(test_uint16_t(0xffff), test_uint16_t(0xffff)).rem, uint16_t(0xffff) % uint16_t(0xffff));

    // [24bit, signed]
    BOOST_CHECK_EQUAL(div(test_int24_t(0), test_int24_t(1)).quot, 0 / 1);
    BOOST_CHECK_EQUAL(div(test_int24_t(0), test_int24_t(1)).rem, 0 % 1);
    BOOST_CHECK_EQUAL(div(test_int24_t(8), test_int24_t(3)).quot, 8 / 3);
    BOOST_CHECK_EQUAL(div(test_int24_t(8), test_int24_t(3)).rem, 8 % 3);
    BOOST_CHECK_EQUAL(div(test_int24_t(9), test_int24_t(3)).quot, 9 / 3);
    BOOST_CHECK_EQUAL(div(test_int24_t(9), test_int24_t(3)).rem, 9 % 3);
    BOOST_CHECK_EQUAL(div(test_int24_t(10), test_int24_t(3)).quot, 10 / 3);
    BOOST_CHECK_EQUAL(div(test_int24_t(10), test_int24_t(3)).rem, 10 % 3);
    BOOST_CHECK_EQUAL(div(test_int24_t(11), test_int24_t(3)).quot, 11 / 3);
    BOOST_CHECK_EQUAL(div(test_int24_t(11), test_int24_t(3)).rem, 11 % 3);

    BOOST_CHECK_EQUAL(div(test_int24_t(0x7fffff), test_int24_t(0x7fffff)).quot, 0x7fffff / 0x7fffff);
    BOOST_CHECK_EQUAL(div(test_int24_t(0x7fffff), test_int24_t(0x7fffff)).rem, 0x7fffff % 0x7fffff);
    BOOST_CHECK_EQUAL(div(test_int24_t(0x7fffff), test_int24_t(0xffffff)).quot, 0x7fffff / -1);
    BOOST_CHECK_EQUAL(div(test_int24_t(0x7fffff), test_int24_t(0xffffff)).rem, 0x7fffff % -1);
    BOOST_CHECK_EQUAL(div(test_int24_t(0xffffff), test_int24_t(0x7fffff)).quot, -1 / 0x7fffff);
    BOOST_CHECK_EQUAL(div(test_int24_t(0xffffff), test_int24_t(0x7fffff)).rem, -1 % 0x7fffff);
    BOOST_CHECK_EQUAL(div(test_int24_t(0xffffff), test_int24_t(0xffffff)).quot, -1 / -1);
    BOOST_CHECK_EQUAL(div(test_int24_t(0xffffff), test_int24_t(0xffffff)).rem, -1 % -1);
}
