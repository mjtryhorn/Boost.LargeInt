// large_int_test_def.cpp - Boost.LargeInt Library test file -----------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#include <boost/limits.hpp> // For std::numeric_limits
#include <boost/cstdint.hpp> // For BOOST_NO_INT64_T
#include <boost/large_int.hpp>
#include <boost/large_int/io.hpp>

#define BOOST_TEST_MODULE boost_large_int_def
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( large_int_def )
{
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
    using boost::large_int::large_int_traits;

    // Check that all pre-defined integer types are of the correct size
    BOOST_CHECK(std::numeric_limits<lint64_t>::digits == 63);
    BOOST_CHECK(std::numeric_limits<luint64_t>::digits == 64);
    BOOST_CHECK(std::numeric_limits<lint96_t>::digits == 95);
    BOOST_CHECK(std::numeric_limits<luint96_t>::digits == 96);
    BOOST_CHECK(std::numeric_limits<lint128_t>::digits == 127);
    BOOST_CHECK(std::numeric_limits<luint128_t>::digits == 128);
    BOOST_CHECK(std::numeric_limits<lint160_t>::digits == 159);
    BOOST_CHECK(std::numeric_limits<luint160_t>::digits == 160);
    BOOST_CHECK(std::numeric_limits<lint192_t>::digits == 191);
    BOOST_CHECK(std::numeric_limits<luint192_t>::digits == 192);
    BOOST_CHECK(std::numeric_limits<lint256_t>::digits == 255);
    BOOST_CHECK(std::numeric_limits<luint256_t>::digits == 256);

    // Check that all pre-defined integer types are correctly signed
    BOOST_CHECK(std::numeric_limits<lint64_t>::is_signed == true);
    BOOST_CHECK(std::numeric_limits<luint64_t>::is_signed == false);
    BOOST_CHECK(std::numeric_limits<lint96_t>::is_signed == true);
    BOOST_CHECK(std::numeric_limits<luint96_t>::is_signed == false);
    BOOST_CHECK(std::numeric_limits<lint128_t>::is_signed == true);
    BOOST_CHECK(std::numeric_limits<luint128_t>::is_signed == false);
    BOOST_CHECK(std::numeric_limits<lint160_t>::is_signed == true);
    BOOST_CHECK(std::numeric_limits<luint160_t>::is_signed == false);
    BOOST_CHECK(std::numeric_limits<lint192_t>::is_signed == true);
    BOOST_CHECK(std::numeric_limits<luint192_t>::is_signed == false);
    BOOST_CHECK(std::numeric_limits<lint256_t>::is_signed == true);
    BOOST_CHECK(std::numeric_limits<luint256_t>::is_signed == false);

    // Check large_int_traits for 64bit large_int types
#ifdef BOOST_NO_INT64_T
    BOOST_CHECK(large_int_traits<lint64_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<lint64_t>::low_bits == 32);
    BOOST_CHECK(large_int_traits<lint64_t>::high_bits == 32);
    BOOST_CHECK(large_int_traits<lint64_t>::size_bits == 64);
    BOOST_CHECK(large_int_traits<luint64_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<luint64_t>::low_bits == 32);
    BOOST_CHECK(large_int_traits<luint64_t>::high_bits == 32);
    BOOST_CHECK(large_int_traits<luint64_t>::size_bits == 64);
#else
    BOOST_CHECK(large_int_traits<lint64_t>::is_large_int == false);
    BOOST_CHECK(large_int_traits<luint64_t>::is_large_int == false);
#endif /* BOOST_NO_INT64_T */

    // Check large_int_traits for 96bit large_int types
    BOOST_CHECK(large_int_traits<lint96_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<lint96_t>::low_bits == 64);
    BOOST_CHECK(large_int_traits<lint96_t>::high_bits == 32);
    BOOST_CHECK(large_int_traits<lint96_t>::size_bits == 96);
    BOOST_CHECK(large_int_traits<luint96_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<luint96_t>::low_bits == 64);
    BOOST_CHECK(large_int_traits<luint96_t>::high_bits == 32);
    BOOST_CHECK(large_int_traits<luint96_t>::size_bits == 96);

    // Check large_int_traits for 128bit large_int types
    BOOST_CHECK(large_int_traits<lint128_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<lint128_t>::low_bits == 64);
    BOOST_CHECK(large_int_traits<lint128_t>::high_bits == 64);
    BOOST_CHECK(large_int_traits<lint128_t>::size_bits == 128);
    BOOST_CHECK(large_int_traits<luint128_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<luint128_t>::low_bits == 64);
    BOOST_CHECK(large_int_traits<luint128_t>::high_bits == 64);
    BOOST_CHECK(large_int_traits<luint128_t>::size_bits == 128);

    // Check large_int_traits for 160bit large_int types
    BOOST_CHECK(large_int_traits<lint160_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<lint160_t>::low_bits == 128);
    BOOST_CHECK(large_int_traits<lint160_t>::high_bits == 32);
    BOOST_CHECK(large_int_traits<lint160_t>::size_bits == 160);
    BOOST_CHECK(large_int_traits<luint160_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<luint160_t>::low_bits == 128);
    BOOST_CHECK(large_int_traits<luint160_t>::high_bits == 32);
    BOOST_CHECK(large_int_traits<luint160_t>::size_bits == 160);

    // Check large_int_traits for 192bit large_int types
    BOOST_CHECK(large_int_traits<lint192_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<lint192_t>::low_bits == 128);
    BOOST_CHECK(large_int_traits<lint192_t>::high_bits == 64);
    BOOST_CHECK(large_int_traits<lint192_t>::size_bits == 192);
    BOOST_CHECK(large_int_traits<luint192_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<luint192_t>::low_bits == 128);
    BOOST_CHECK(large_int_traits<luint192_t>::high_bits == 64);
    BOOST_CHECK(large_int_traits<luint192_t>::size_bits == 192);

    // Check large_int_traits for 256bit large_int types
    BOOST_CHECK(large_int_traits<lint256_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<lint256_t>::low_bits == 128);
    BOOST_CHECK(large_int_traits<lint256_t>::high_bits == 128);
    BOOST_CHECK(large_int_traits<lint256_t>::size_bits == 256);
    BOOST_CHECK(large_int_traits<luint256_t>::is_large_int == true);
    BOOST_CHECK(large_int_traits<luint256_t>::low_bits == 128);
    BOOST_CHECK(large_int_traits<luint256_t>::high_bits == 128);
    BOOST_CHECK(large_int_traits<luint256_t>::size_bits == 256);
}
