// large_int_test_version.cpp - Boost.LargeInt Library test file -------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#include <boost/large_int.hpp>

#define BOOST_TEST_MODULE boost_large_int_version
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( large_int_version )
{
    // This test will need to be updated whenever
    // the version of Boost.LargeInt changes
    BOOST_REQUIRE(BOOST_IS_DEFINED(BOOST_LARGE_INT_VERSION));
    BOOST_CHECK((BOOST_LARGE_INT_VERSION % 100) == 0); // Revision
    BOOST_CHECK((BOOST_LARGE_INT_VERSION / 100 % 1000) == 0); // Minor
    BOOST_CHECK((BOOST_LARGE_INT_VERSION / 100000) == 1); // Major
}
