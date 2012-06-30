// large_int_test_limits.cpp - Boost.LargeInt Library test file --------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#include <boost/limits.hpp> // For std::numeric_limits
#include <boost/cstdint.hpp> // For int8_t, int16_t, int32_t,
                             //     uint8_t, uint16_t, uint32_t
#include <boost/large_int.hpp>
#include <boost/large_int/io.hpp>

#define BOOST_TEST_MODULE boost_large_int_limits
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( large_int_limits )
{
    using boost::large_int::large_int;
    using boost::large_int::lint64_t;
    using boost::large_int::luint64_t;
    using boost::large_int::lint96_t;
    using boost::large_int::luint96_t;
    using boost::large_int::lint128_t;
    using boost::large_int::luint128_t;
    using boost::large_int::lint160_t;
    using boost::large_int::luint160_t;
    using boost::large_int::lint192_t;
    using boost::large_int::luint192_t;
    using boost::large_int::lint256_t;
    using boost::large_int::luint256_t;

    // Declare signed and unsigned 16 and 32bit integers for testing
    typedef large_int<uint8_t, int8_t> test_int16_t;
    typedef large_int<uint8_t, uint8_t> test_uint16_t;
    typedef large_int<test_uint16_t, test_int16_t> test_int32_t;
    typedef large_int<test_uint16_t, test_uint16_t> test_uint32_t;

    // Check std::numeric_limits for test_int16_t
    BOOST_CHECK(std::numeric_limits<test_int16_t>::is_specialized);
    BOOST_CHECK((std::numeric_limits<test_int16_t>::min)() == (std::numeric_limits<int16_t>::min)());
    BOOST_CHECK((std::numeric_limits<test_int16_t>::max)() == (std::numeric_limits<int16_t>::max)());
    BOOST_CHECK(std::numeric_limits<test_int16_t>::epsilon() == std::numeric_limits<int16_t>::epsilon());
    BOOST_CHECK(std::numeric_limits<test_int16_t>::round_error() == std::numeric_limits<int16_t>::round_error());
    BOOST_CHECK(std::numeric_limits<test_int16_t>::infinity() == std::numeric_limits<int16_t>::infinity());
    BOOST_CHECK(std::numeric_limits<test_int16_t>::quiet_NaN() == std::numeric_limits<int16_t>::quiet_NaN());
    BOOST_CHECK(std::numeric_limits<test_int16_t>::signaling_NaN() == std::numeric_limits<int16_t>::signaling_NaN());
    BOOST_CHECK(std::numeric_limits<test_int16_t>::denorm_min() == std::numeric_limits<int16_t>::denorm_min());
    BOOST_CHECK(std::numeric_limits<test_int16_t>::digits == std::numeric_limits<int16_t>::digits);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::digits10 == std::numeric_limits<int16_t>::digits10);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::is_signed == std::numeric_limits<int16_t>::is_signed);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::is_integer == std::numeric_limits<int16_t>::is_integer);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::is_exact == std::numeric_limits<int16_t>::is_exact);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::radix == std::numeric_limits<int16_t>::radix);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::min_exponent == std::numeric_limits<int16_t>::min_exponent);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::min_exponent10 == std::numeric_limits<int16_t>::min_exponent10);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::max_exponent == std::numeric_limits<int16_t>::max_exponent);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::max_exponent10 == std::numeric_limits<int16_t>::max_exponent10);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::has_infinity == std::numeric_limits<int16_t>::has_infinity);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::has_quiet_NaN == std::numeric_limits<int16_t>::has_quiet_NaN);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::has_signaling_NaN == std::numeric_limits<int16_t>::has_signaling_NaN);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::has_denorm == std::numeric_limits<int16_t>::has_denorm);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::has_denorm_loss == std::numeric_limits<int16_t>::has_denorm_loss);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::is_iec559 == std::numeric_limits<int16_t>::is_iec559);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::is_bounded == std::numeric_limits<int16_t>::is_bounded);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::is_modulo == std::numeric_limits<int16_t>::is_modulo);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::traps == std::numeric_limits<int16_t>::traps);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::tinyness_before == std::numeric_limits<int16_t>::tinyness_before);
    BOOST_CHECK(std::numeric_limits<test_int16_t>::round_style == std::numeric_limits<int16_t>::round_style);

    // Check std::numeric_limits for test_uint16_t
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::is_specialized);
    BOOST_CHECK((std::numeric_limits<test_uint16_t>::min)() == (std::numeric_limits<uint16_t>::min)());
    BOOST_CHECK((std::numeric_limits<test_uint16_t>::max)() == (std::numeric_limits<uint16_t>::max)());
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::epsilon() == std::numeric_limits<uint16_t>::epsilon());
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::round_error() == std::numeric_limits<uint16_t>::round_error());
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::infinity() == std::numeric_limits<uint16_t>::infinity());
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::quiet_NaN() == std::numeric_limits<uint16_t>::quiet_NaN());
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::signaling_NaN() == std::numeric_limits<uint16_t>::signaling_NaN());
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::denorm_min() == std::numeric_limits<uint16_t>::denorm_min());
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::digits == std::numeric_limits<uint16_t>::digits);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::digits10 == std::numeric_limits<uint16_t>::digits10);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::is_signed == std::numeric_limits<uint16_t>::is_signed);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::is_integer == std::numeric_limits<uint16_t>::is_integer);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::is_exact == std::numeric_limits<uint16_t>::is_exact);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::radix == std::numeric_limits<uint16_t>::radix);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::min_exponent == std::numeric_limits<uint16_t>::min_exponent);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::min_exponent10 == std::numeric_limits<uint16_t>::min_exponent10);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::max_exponent == std::numeric_limits<uint16_t>::max_exponent);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::max_exponent10 == std::numeric_limits<uint16_t>::max_exponent10);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::has_infinity == std::numeric_limits<uint16_t>::has_infinity);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::has_quiet_NaN == std::numeric_limits<uint16_t>::has_quiet_NaN);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::has_signaling_NaN == std::numeric_limits<uint16_t>::has_signaling_NaN);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::has_denorm == std::numeric_limits<uint16_t>::has_denorm);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::has_denorm_loss == std::numeric_limits<uint16_t>::has_denorm_loss);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::is_iec559 == std::numeric_limits<uint16_t>::is_iec559);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::is_bounded == std::numeric_limits<uint16_t>::is_bounded);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::is_modulo == std::numeric_limits<uint16_t>::is_modulo);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::traps == std::numeric_limits<uint16_t>::traps);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::tinyness_before == std::numeric_limits<uint16_t>::tinyness_before);
    BOOST_CHECK(std::numeric_limits<test_uint16_t>::round_style == std::numeric_limits<uint16_t>::round_style);

    // Check std::numeric_limits for test_int32_t
    BOOST_CHECK(std::numeric_limits<test_int32_t>::is_specialized);
    BOOST_CHECK((std::numeric_limits<test_int32_t>::min)() == (std::numeric_limits<int32_t>::min)());
    BOOST_CHECK((std::numeric_limits<test_int32_t>::max)() == (std::numeric_limits<int32_t>::max)());
    BOOST_CHECK(std::numeric_limits<test_int32_t>::epsilon() == std::numeric_limits<int32_t>::epsilon());
    BOOST_CHECK(std::numeric_limits<test_int32_t>::round_error() == std::numeric_limits<int32_t>::round_error());
    BOOST_CHECK(std::numeric_limits<test_int32_t>::infinity() == std::numeric_limits<int32_t>::infinity());
    BOOST_CHECK(std::numeric_limits<test_int32_t>::quiet_NaN() == std::numeric_limits<int32_t>::quiet_NaN());
    BOOST_CHECK(std::numeric_limits<test_int32_t>::signaling_NaN() == std::numeric_limits<int32_t>::signaling_NaN());
    BOOST_CHECK(std::numeric_limits<test_int32_t>::denorm_min() == std::numeric_limits<int32_t>::denorm_min());
    BOOST_CHECK(std::numeric_limits<test_int32_t>::digits == std::numeric_limits<int32_t>::digits);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::digits10 == std::numeric_limits<int32_t>::digits10);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::is_signed == std::numeric_limits<int32_t>::is_signed);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::is_integer == std::numeric_limits<int32_t>::is_integer);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::is_exact == std::numeric_limits<int32_t>::is_exact);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::radix == std::numeric_limits<int32_t>::radix);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::min_exponent == std::numeric_limits<int32_t>::min_exponent);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::min_exponent10 == std::numeric_limits<int32_t>::min_exponent10);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::max_exponent == std::numeric_limits<int32_t>::max_exponent);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::max_exponent10 == std::numeric_limits<int32_t>::max_exponent10);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::has_infinity == std::numeric_limits<int32_t>::has_infinity);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::has_quiet_NaN == std::numeric_limits<int32_t>::has_quiet_NaN);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::has_signaling_NaN == std::numeric_limits<int32_t>::has_signaling_NaN);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::has_denorm == std::numeric_limits<int32_t>::has_denorm);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::has_denorm_loss == std::numeric_limits<int32_t>::has_denorm_loss);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::is_iec559 == std::numeric_limits<int32_t>::is_iec559);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::is_bounded == std::numeric_limits<int32_t>::is_bounded);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::is_modulo == std::numeric_limits<int32_t>::is_modulo);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::traps == std::numeric_limits<int32_t>::traps);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::tinyness_before == std::numeric_limits<int32_t>::tinyness_before);
    BOOST_CHECK(std::numeric_limits<test_int32_t>::round_style == std::numeric_limits<int32_t>::round_style);

    // Check std::numeric_limits for test_uint32_t
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::is_specialized);
    BOOST_CHECK((std::numeric_limits<test_uint32_t>::min)() == (std::numeric_limits<uint32_t>::min)());
    BOOST_CHECK((std::numeric_limits<test_uint32_t>::max)() == (std::numeric_limits<uint32_t>::max)());
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::epsilon() == std::numeric_limits<uint32_t>::epsilon());
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::round_error() == std::numeric_limits<uint32_t>::round_error());
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::infinity() == std::numeric_limits<uint32_t>::infinity());
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::quiet_NaN() == std::numeric_limits<uint32_t>::quiet_NaN());
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::signaling_NaN() == std::numeric_limits<uint32_t>::signaling_NaN());
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::denorm_min() == std::numeric_limits<uint32_t>::denorm_min());
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::digits == std::numeric_limits<uint32_t>::digits);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::digits10 == std::numeric_limits<uint32_t>::digits10);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::is_signed == std::numeric_limits<uint32_t>::is_signed);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::is_integer == std::numeric_limits<uint32_t>::is_integer);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::is_exact == std::numeric_limits<uint32_t>::is_exact);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::radix == std::numeric_limits<uint32_t>::radix);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::min_exponent == std::numeric_limits<uint32_t>::min_exponent);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::min_exponent10 == std::numeric_limits<uint32_t>::min_exponent10);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::max_exponent == std::numeric_limits<uint32_t>::max_exponent);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::max_exponent10 == std::numeric_limits<uint32_t>::max_exponent10);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::has_infinity == std::numeric_limits<uint32_t>::has_infinity);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::has_quiet_NaN == std::numeric_limits<uint32_t>::has_quiet_NaN);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::has_signaling_NaN == std::numeric_limits<uint32_t>::has_signaling_NaN);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::has_denorm == std::numeric_limits<uint32_t>::has_denorm);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::has_denorm_loss == std::numeric_limits<uint32_t>::has_denorm_loss);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::is_iec559 == std::numeric_limits<uint32_t>::is_iec559);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::is_bounded == std::numeric_limits<uint32_t>::is_bounded);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::is_modulo == std::numeric_limits<uint32_t>::is_modulo);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::traps == std::numeric_limits<uint32_t>::traps);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::tinyness_before == std::numeric_limits<uint32_t>::tinyness_before);
    BOOST_CHECK(std::numeric_limits<test_uint32_t>::round_style == std::numeric_limits<uint32_t>::round_style);

    // Check digits10 for predefined large_int types
    // (this test is necessary as the digits10 is
    // calculated from an approximation of log10(2))
    BOOST_CHECK(std::numeric_limits<lint64_t>::digits10 == 18);
    BOOST_CHECK(std::numeric_limits<luint64_t>::digits10 == 19);
    BOOST_CHECK(std::numeric_limits<lint96_t>::digits10 == 28);
    BOOST_CHECK(std::numeric_limits<luint96_t>::digits10 == 28);
    BOOST_CHECK(std::numeric_limits<lint128_t>::digits10 == 38);
    BOOST_CHECK(std::numeric_limits<luint128_t>::digits10 == 38);
    BOOST_CHECK(std::numeric_limits<lint160_t>::digits10 == 47);
    BOOST_CHECK(std::numeric_limits<luint160_t>::digits10 == 48);
    BOOST_CHECK(std::numeric_limits<lint192_t>::digits10 == 57);
    BOOST_CHECK(std::numeric_limits<luint192_t>::digits10 == 57);
    BOOST_CHECK(std::numeric_limits<lint256_t>::digits10 == 76);
    BOOST_CHECK(std::numeric_limits<luint256_t>::digits10 == 77);
}
