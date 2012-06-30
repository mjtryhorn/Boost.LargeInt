// large_int_test_traits.cpp - Boost.LargeInt Library test file --------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#include <typeinfo> // For typeid
#include <boost/cstdint.hpp> // For int8_t, int16_t, uint8_t, uint16_t
#include <boost/large_int.hpp>
#include <boost/large_int/io.hpp>

#define BOOST_TEST_MODULE boost_large_int_traits
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( large_int_traits )
{
    using boost::large_int::large_int_traits;
    using boost::large_int::large_int;

    // Declare signed and unsigned 16, 24 and 32bit integers for testing
    typedef large_int<uint8_t, int8_t> test_int16_t;
    typedef large_int<uint8_t, uint8_t> test_uint16_t;
    typedef large_int<test_uint16_t, int8_t> test_int24_t;
    typedef large_int<test_uint16_t, uint8_t> test_uint24_t;
    typedef large_int<test_uint16_t, test_int16_t> test_int32_t;
    typedef large_int<test_uint16_t, test_uint16_t> test_uint32_t;

    // Check large_int_traits internal types
    BOOST_CHECK(typeid( large_int_traits<test_int16_t>::low_part_type ) == typeid( uint8_t ));
    BOOST_CHECK(typeid( large_int_traits<test_int16_t>::high_part_type ) == typeid( int8_t ));
    BOOST_CHECK(typeid( large_int_traits<test_uint16_t>::low_part_type ) == typeid( uint8_t ));
    BOOST_CHECK(typeid( large_int_traits<test_uint16_t>::high_part_type ) == typeid( uint8_t ));
    BOOST_CHECK(typeid( large_int_traits<test_int24_t>::low_part_type ) == typeid( test_uint16_t ));
    BOOST_CHECK(typeid( large_int_traits<test_int24_t>::high_part_type ) == typeid( int8_t ));
    BOOST_CHECK(typeid( large_int_traits<test_uint24_t>::low_part_type ) == typeid( test_uint16_t ));
    BOOST_CHECK(typeid( large_int_traits<test_uint24_t>::high_part_type ) == typeid( uint8_t ));
    BOOST_CHECK(typeid( large_int_traits<test_int32_t>::low_part_type ) == typeid( test_uint16_t ));
    BOOST_CHECK(typeid( large_int_traits<test_int32_t>::high_part_type ) == typeid( test_int16_t ));
    BOOST_CHECK(typeid( large_int_traits<test_uint32_t>::low_part_type ) == typeid( test_uint16_t ));
    BOOST_CHECK(typeid( large_int_traits<test_uint32_t>::high_part_type ) == typeid( test_uint16_t ));

    // Check large_int_traits constants
    BOOST_CHECK(large_int_traits<int16_t>::is_large_int == false);
    BOOST_CHECK(large_int_traits<uint16_t>::is_large_int == false);
    BOOST_CHECK(large_int_traits<test_int16_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<test_int16_t>::low_bits == 8);
    BOOST_CHECK(large_int_traits<test_int16_t>::high_bits == 8);
    BOOST_CHECK(large_int_traits<test_int16_t>::size_bits == 16);
    BOOST_CHECK(large_int_traits<test_uint16_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<test_uint16_t>::low_bits == 8);
    BOOST_CHECK(large_int_traits<test_uint16_t>::high_bits == 8);
    BOOST_CHECK(large_int_traits<test_uint16_t>::size_bits == 16);
    BOOST_CHECK(large_int_traits<test_int24_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<test_int24_t>::low_bits == 16);
    BOOST_CHECK(large_int_traits<test_int24_t>::high_bits == 8);
    BOOST_CHECK(large_int_traits<test_int24_t>::size_bits == 24);
    BOOST_CHECK(large_int_traits<test_uint24_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<test_uint24_t>::low_bits == 16);
    BOOST_CHECK(large_int_traits<test_uint24_t>::high_bits == 8);
    BOOST_CHECK(large_int_traits<test_uint24_t>::size_bits == 24);
    BOOST_CHECK(large_int_traits<test_int32_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<test_int32_t>::low_bits == 16);
    BOOST_CHECK(large_int_traits<test_int32_t>::high_bits == 16);
    BOOST_CHECK(large_int_traits<test_int32_t>::size_bits == 32);
    BOOST_CHECK(large_int_traits<test_uint32_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<test_uint32_t>::low_bits == 16);
    BOOST_CHECK(large_int_traits<test_uint32_t>::high_bits == 16);
    BOOST_CHECK(large_int_traits<test_uint32_t>::size_bits == 32);

    // Check large_int_traits::lt (for both equivalent and differing integral types)
    // [16bit vs. 16bit, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0), test_int16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0), test_int16_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(1), test_int16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(1), test_int16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(1), test_int16_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(2), test_int16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(2), test_int16_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0), test_int16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(-1), test_int16_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(-1), test_int16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(-1), test_int16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(-2), test_int16_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(-2), test_int16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0x7fff), test_int16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0x7fff), test_int16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0xffff), test_int16_t(0x7fff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0xffff), test_int16_t(0xffff)), false);

    // [16bit vs. 24bit, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0), test_int24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0), test_int24_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(1), test_int24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(1), test_int24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(1), test_int24_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(2), test_int24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(2), test_int24_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0), test_int24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(-1), test_int24_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(-1), test_int24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(-1), test_int24_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(-2), test_int24_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(-2), test_int24_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0x7fff), test_int24_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0x7fff), test_int24_t(0xffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0xffff), test_int24_t(0x7fff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0xffff), test_int24_t(0xffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0x7fff), test_int24_t(0x10000)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0xffff), test_int24_t(0x10000)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0x7fff), test_int24_t(0xffffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt(test_int16_t(0xffff), test_int24_t(0xffffff)), false);

    // [24bit vs. 16bit, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0), test_int16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0), test_int16_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(1), test_int16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(1), test_int16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(1), test_int16_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(2), test_int16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(2), test_int16_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0), test_int16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(-1), test_int16_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(-1), test_int16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(-1), test_int16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(-2), test_int16_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(-2), test_int16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0x7fff), test_int16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0x7fff), test_int16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0xffff), test_int16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0xffff), test_int16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0x10000), test_int16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0x10000), test_int16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0xffffff), test_int16_t(0x7fff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0xffffff), test_int16_t(0xffff)), false);

    // [24bit vs. 24bit, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0), test_int24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0), test_int24_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(1), test_int24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(1), test_int24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(1), test_int24_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(2), test_int24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(2), test_int24_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0), test_int24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(-1), test_int24_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(-1), test_int24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(-1), test_int24_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(-2), test_int24_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(-2), test_int24_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0x7fffff), test_int24_t(0x7fffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0x7fffff), test_int24_t(0xffffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0xffffff), test_int24_t(0x7fffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt(test_int24_t(0xffffff), test_int24_t(0xffffff)), false);

    // [16bit vs. 16bit, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0), test_uint16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0), test_uint16_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(1), test_uint16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(1), test_uint16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(1), test_uint16_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(2), test_uint16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(2), test_uint16_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0), test_uint16_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(-1), test_uint16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(-1), test_uint16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(-1), test_uint16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(-2), test_uint16_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(-2), test_uint16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0x7fff), test_uint16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0x7fff), test_uint16_t(0xffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0xffff), test_uint16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0xffff), test_uint16_t(0xffff)), false);

    // [16bit vs. 24bit, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0), test_uint24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0), test_uint24_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(1), test_uint24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(1), test_uint24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(1), test_uint24_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(2), test_uint24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(2), test_uint24_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0), test_uint24_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(-1), test_uint24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(-1), test_uint24_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(-1), test_uint24_t(-2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(-2), test_uint24_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(-2), test_uint24_t(-2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0x7fff), test_uint24_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0x7fff), test_uint24_t(0xffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0xffff), test_uint24_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0xffff), test_uint24_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0x7fff), test_uint24_t(0x10000)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0xffff), test_uint24_t(0x10000)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0x7fff), test_uint24_t(0xffffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt(test_uint16_t(0xffff), test_uint24_t(0xffffff)), true);

    // [24bit vs. 16bit, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0), test_uint16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0), test_uint16_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(1), test_uint16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(1), test_uint16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(1), test_uint16_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(2), test_uint16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(2), test_uint16_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0), test_uint16_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(-1), test_uint16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(-1), test_uint16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(-1), test_uint16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(-2), test_uint16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(-2), test_uint16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0x7fff), test_uint16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0x7fff), test_uint16_t(0xffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0xffff), test_uint16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0xffff), test_uint16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0x10000), test_uint16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0x10000), test_uint16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0xffffff), test_uint16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0xffffff), test_uint16_t(0xffff)), false);

    // [24bit vs. 24bit, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0), test_uint24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0), test_uint24_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(1), test_uint24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(1), test_uint24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(1), test_uint24_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(2), test_uint24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(2), test_uint24_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0), test_uint24_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(-1), test_uint24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(-1), test_uint24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(-1), test_uint24_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(-2), test_uint24_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(-2), test_uint24_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0x7fffff), test_uint24_t(0x7fffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0x7fffff), test_uint24_t(0xffffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0xffffff), test_uint24_t(0x7fffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt(test_uint24_t(0xffffff), test_uint24_t(0xffffff)), false);

    // Check large_int_traits::eq (for both equivalent and differing integral types)
    // [16bit vs. 16bit, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0), test_int16_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0), test_int16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(1), test_int16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(1), test_int16_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(1), test_int16_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(2), test_int16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(2), test_int16_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0), test_int16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(-1), test_int16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(-1), test_int16_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(-1), test_int16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(-2), test_int16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(-2), test_int16_t(-2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0x7fff), test_int16_t(0x7fff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0x7fff), test_int16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0xffff), test_int16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0xffff), test_int16_t(0xffff)), true);

    // [16bit vs. 24bit, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0), test_int24_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0), test_int24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(1), test_int24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(1), test_int24_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(1), test_int24_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(2), test_int24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(2), test_int24_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0), test_int24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(-1), test_int24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(-1), test_int24_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(-1), test_int24_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(-2), test_int24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(-2), test_int24_t(-2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0x7fff), test_int24_t(0x7fff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0x7fff), test_int24_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0xffff), test_int24_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0xffff), test_int24_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0x7fff), test_int24_t(0x10000)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0xffff), test_int24_t(0x10000)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0x7fff), test_int24_t(0xffffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq(test_int16_t(0xffff), test_int24_t(0xffffff)), true);

    // [24bit vs. 16bit, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0), test_int16_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0), test_int16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(1), test_int16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(1), test_int16_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(1), test_int16_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(2), test_int16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(2), test_int16_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0), test_int16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(-1), test_int16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(-1), test_int16_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(-1), test_int16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(-2), test_int16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(-2), test_int16_t(-2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0x7fff), test_int16_t(0x7fff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0x7fff), test_int16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0xffff), test_int16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0xffff), test_int16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0x10000), test_int16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0x10000), test_int16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0xffffff), test_int16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0xffffff), test_int16_t(0xffff)), true);

    // [24bit vs. 24bit, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0), test_int24_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0), test_int24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(1), test_int24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(1), test_int24_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(1), test_int24_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(2), test_int24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(2), test_int24_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0), test_int24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(-1), test_int24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(-1), test_int24_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(-1), test_int24_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(-2), test_int24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(-2), test_int24_t(-2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0x7fffff), test_int24_t(0x7fffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0x7fffff), test_int24_t(0xffffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0xffffff), test_int24_t(0x7fffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq(test_int24_t(0xffffff), test_int24_t(0xffffff)), true);

    // [16bit vs. 16bit, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0), test_uint16_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0), test_uint16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(1), test_uint16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(1), test_uint16_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(1), test_uint16_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(2), test_uint16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(2), test_uint16_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0), test_uint16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(-1), test_uint16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(-1), test_uint16_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(-1), test_uint16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(-2), test_uint16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(-2), test_uint16_t(-2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0x7fff), test_uint16_t(0x7fff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0x7fff), test_uint16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0xffff), test_uint16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0xffff), test_uint16_t(0xffff)), true);

    // [16bit vs. 24bit, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0), test_uint24_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0), test_uint24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(1), test_uint24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(1), test_uint24_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(1), test_uint24_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(2), test_uint24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(2), test_uint24_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0), test_uint24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(-1), test_uint24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(-1), test_uint24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(-1), test_uint24_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(-2), test_uint24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(-2), test_uint24_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0x7fff), test_uint24_t(0x7fff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0x7fff), test_uint24_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0xffff), test_uint24_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0xffff), test_uint24_t(0xffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0x7fff), test_uint24_t(0x10000)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0xffff), test_uint24_t(0x10000)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0x7fff), test_uint24_t(0xffffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq(test_uint16_t(0xffff), test_uint24_t(0xffffff)), false);

    // [24bit vs. 16bit, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0), test_uint16_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0), test_uint16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(1), test_uint16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(1), test_uint16_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(1), test_uint16_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(2), test_uint16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(2), test_uint16_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0), test_uint16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(-1), test_uint16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(-1), test_uint16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(-1), test_uint16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(-2), test_uint16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(-2), test_uint16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0x7fff), test_uint16_t(0x7fff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0x7fff), test_uint16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0xffff), test_uint16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0xffff), test_uint16_t(0xffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0x10000), test_uint16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0x10000), test_uint16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0xffffff), test_uint16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0xffffff), test_uint16_t(0xffff)), false);

    // [24bit vs. 24bit, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0), test_uint24_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0), test_uint24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(1), test_uint24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(1), test_uint24_t(1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(1), test_uint24_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(2), test_uint24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(2), test_uint24_t(2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0), test_uint24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(-1), test_uint24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(-1), test_uint24_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(-1), test_uint24_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(-2), test_uint24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(-2), test_uint24_t(-2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0x7fffff), test_uint24_t(0x7fffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0x7fffff), test_uint24_t(0xffffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0xffffff), test_uint24_t(0x7fffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq(test_uint24_t(0xffffff), test_uint24_t(0xffffff)), true);

    // Check large_int_traits::lt_literal
    // [16bit vs. literal, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(0), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(0), 1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(1), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(1), 2), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(2), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(2), 2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(0), -1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(-1), 0), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(-1), -1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(-1), -2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(-2), -1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(-2), -2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(0x7fff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(0x7fff), 0xffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(0xffff), 0x7fff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(0xffff), 0xffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(0x7fff), 0x10000), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::lt_literal(test_int16_t(0xffff), 0x10000), true);

    // [24bit vs. literal, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0), 1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(1), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(1), 2), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(2), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(2), 2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0), -1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(-1), 0), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(-1), -1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(-1), -2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(-2), -1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(-2), -2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0x7fff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0x7fff), 0xffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0xffff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0xffff), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0x10000), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0x10000), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0xffffff), 0x7fff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0xffffff), 0xffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0x7fffff), 0x7fffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::lt_literal(test_int24_t(0xffffff), 0x7fffff), true);

    // [16bit vs. literal, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(0), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(0), 1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(1), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(1), 2), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(2), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(2), 2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(0), -1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(-1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(-1), -1), true); // [Due to promotion of the literal as unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(-1), -2), true); // [Due to promotion of the literal as unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(-2), -1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(-2), -2), true); // [Due to promotion of the literal as unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_int16_t(0x7fff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_int16_t(0x7fff), 0xffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_int16_t(0xffff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_int16_t(0xffff), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(0x7fff), 0x10000), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(0xffff), 0x10000), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(0x7fff), 0xffffffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::lt_literal(test_uint16_t(0xffff), 0xffffffff), true);

    // [24bit vs. literal, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0), 1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(1), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(1), 2), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(2), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(2), 2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0), -1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(-1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0x7fff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0x7fff), 0xffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0xffff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0xffff), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0x10000), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0x10000), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0xffffff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0xffffff), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0x7fffff), 0x7fffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0x7fffff), 0xffffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0xffffff), 0x7fffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::lt_literal(test_uint24_t(0xffffff), 0xffffff), false);

    // Check large_int_traits::eq_literal
    // [16bit vs. literal, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(0), 0), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(0), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(1), 1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(1), 2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(2), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(2), 2), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(0), -1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(-1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(-1), -1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(-1), -2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(-2), -1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(-2), -2), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(0x7fff), 0x7fff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(0x7fff), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(0xffff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(0xffff), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(0x7fff), 0x10000), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::eq_literal(test_int16_t(0xffff), 0x10000), false);

    // [24bit vs. literal, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0), 0), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(1), 1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(1), 2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(2), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(2), 2), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0), -1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(-1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(-1), -1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(-1), -2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(-2), -1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(-2), -2), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0x7fff), 0x7fff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0x7fff), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0xffff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0xffff), 0xffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0x10000), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0x10000), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0xffffff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0xffffff), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0x7fffff), 0x7fffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::eq_literal(test_int24_t(0x7fffff), 0xffffff), false);

    // [16bit vs. literal, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(0), 0), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(0), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(1), 1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(1), 2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(2), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(2), 2), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(0), -1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(-1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(-1), -1), false); // [Due to promotion of the literal as unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(-1), -2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(-2), -1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(-2), -2), false); // [Due to promotion of the literal as unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(0x7fff), 0x7fff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(0x7fff), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(0xffff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(0xffff), 0xffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(0x7fff), 0x10000), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(0xffff), 0x10000), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(0x7fff), 0xffffffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::eq_literal(test_uint16_t(0xffff), 0xffffffff), false);

    // [24bit vs. literal, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0), 0), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(1), 1), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(1), 2), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(2), 1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(2), 2), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0), -1), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(-1), 0), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0x7fff), 0x7fff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0x7fff), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0xffff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0xffff), 0xffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0x10000), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0x10000), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0xffffff), 0x7fff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0xffffff), 0xffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0x7fffff), 0x7fffff), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0x7fffff), 0xffffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0xffffff), 0x7fffff), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::eq_literal(test_uint24_t(0xffffff), 0xffffff), true);

    // Check large_int_traits::is_neg
    // [16, 24 & 32bit, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::is_neg(test_int16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::is_neg(test_int16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::is_neg(test_int16_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::is_neg(test_int16_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::is_neg(test_int16_t(-2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::is_neg(test_int16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::is_neg(test_int16_t(0xffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::is_neg(test_int24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::is_neg(test_int24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::is_neg(test_int24_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::is_neg(test_int24_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::is_neg(test_int24_t(-2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::is_neg(test_int24_t(0x7fffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::is_neg(test_int24_t(0xffffff)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int32_t>::is_neg(test_int32_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int32_t>::is_neg(test_int32_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int32_t>::is_neg(test_int32_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int32_t>::is_neg(test_int32_t(-1)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int32_t>::is_neg(test_int32_t(-2)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int32_t>::is_neg(test_int32_t(0x7fffffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int32_t>::is_neg(test_int32_t(0xffffffff)), true);

    // [16, 24 & 32bit, unsigned (always non-negative)]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::is_neg(test_uint16_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::is_neg(test_uint16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::is_neg(test_uint16_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::is_neg(test_uint16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::is_neg(test_uint16_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::is_neg(test_uint16_t(0x7fff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::is_neg(test_uint16_t(0xffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::is_neg(test_uint24_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::is_neg(test_uint24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::is_neg(test_uint24_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::is_neg(test_uint24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::is_neg(test_uint24_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::is_neg(test_uint24_t(0x7fffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::is_neg(test_uint24_t(0xffffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint32_t>::is_neg(test_uint32_t(0)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint32_t>::is_neg(test_uint32_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint32_t>::is_neg(test_uint32_t(2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint32_t>::is_neg(test_uint32_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint32_t>::is_neg(test_uint32_t(-2)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint32_t>::is_neg(test_uint32_t(0x7fffffff)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint32_t>::is_neg(test_uint32_t(0xffffffff)), false);

    // Check large_int_traits::is_zero
    // [16, 24 & 32bit, signed]
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::is_zero(test_int16_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::is_zero(test_int16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int16_t>::is_zero(test_int16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::is_zero(test_int24_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::is_zero(test_int24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int24_t>::is_zero(test_int24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int32_t>::is_zero(test_int32_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_int32_t>::is_zero(test_int32_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_int32_t>::is_zero(test_int32_t(-1)), false);

    // [16, 24 & 24bit, unsigned]
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::is_zero(test_uint16_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::is_zero(test_uint16_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint16_t>::is_zero(test_uint16_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::is_zero(test_uint24_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::is_zero(test_uint24_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint24_t>::is_zero(test_uint24_t(-1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint32_t>::is_zero(test_uint32_t(0)), true);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint32_t>::is_zero(test_uint32_t(1)), false);
    BOOST_CHECK_EQUAL(large_int_traits<test_uint32_t>::is_zero(test_uint32_t(-1)), false);
}
