// def.hpp - Boost.LargeInt Library header file ------------------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#ifndef BOOST_LARGE_INT_DEF_HPP
#define BOOST_LARGE_INT_DEF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

#include <boost/cstdint.hpp> // For int32_t, uint32_t,
                             //     int64_t, uint64_t,
                             //     BOOST_NO_INT64_T
#include <boost/large_int/base.hpp> // For large_int

namespace boost {
namespace large_int {

// Types --
#ifdef BOOST_NO_INT64_T
// The underlying platform has no built-in support for 64bit integers.
// Define 64bit large_int types as compositions of 32bit built-in
// integer types (which are guaranteed to be available).
typedef large_int<uint32_t, int32_t> lint64_t;
typedef large_int<uint32_t, uint32_t> luint64_t;
#else
// The underlying platform supports 64bit integers.
// Use them in preference to large_int.
typedef int64_t lint64_t;
typedef uint64_t luint64_t;
#endif // BOOST_NO_INT64_T

typedef large_int<luint64_t, int32_t> lint96_t;
typedef large_int<luint64_t, uint32_t> luint96_t;
typedef large_int<luint64_t, lint64_t> lint128_t;
typedef large_int<luint64_t, luint64_t> luint128_t;
typedef large_int<luint128_t, int32_t> lint160_t;
typedef large_int<luint128_t, uint32_t> luint160_t;
typedef large_int<luint128_t, lint64_t> lint192_t;
typedef large_int<luint128_t, luint64_t> luint192_t;
typedef large_int<luint128_t, lint128_t> lint256_t;
typedef large_int<luint128_t, luint128_t> luint256_t;

} // namespace large_int
} // namespace boost

#endif // BOOST_LARGE_INT_DEF_HPP
