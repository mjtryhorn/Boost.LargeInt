// large_int.hpp - Boost.LargeInt Library header file ------------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#ifndef BOOST_LARGE_INT_HPP
#define BOOST_LARGE_INT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

// Note that boost/large_int/io.hpp is NOT included in this file listing,
// and must be included explicitly where required.  This is both because
// the standard streaming headers carry a high compilation overhead, and
// because this functionality is strictly optional.
#include <boost/large_int/fwd.hpp>
#include <boost/large_int/base.hpp>
#include <boost/large_int/cast.hpp>
#include <boost/large_int/div.hpp>
#include <boost/large_int/limits.hpp>
#include <boost/large_int/traits.hpp>
#include <boost/large_int/shift.hpp>
#include <boost/large_int/utils.hpp>
#include <boost/large_int/def.hpp>
#include <boost/large_int/version.hpp>

#include <boost/large_int/impl/base.ipp>

#endif // BOOST_LARGE_INT_HPP
