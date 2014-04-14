// limits.hpp - Boost.LargeInt Library header file ---------------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#ifndef BOOST_LARGE_INT_LIMITS_HPP
#define BOOST_LARGE_INT_LIMITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

#include <boost/limits.hpp> // For std::numeric_limits
#include <boost/config.hpp> // For BOOST_STATIC_CONSTANT,
                            //     BOOST_PREVENT_MACRO_SUBSTITUTION
#include <boost/large_int/base.hpp> // For large_int

// Declare a partial specialization of class std::numeric_limits
// for all boost::large_int::large_int types, as provisioned by
// the C++98 standard, section 17.4.3.1 ("Reserved names").
namespace std
{

// Types --
template<class T, class U>
class numeric_limits< ::boost::large_int::large_int<T, U> >
{
public:
    BOOST_STATIC_CONSTANT(bool, is_specialized = true);

    // Please note: Borland C++ 5.6.4 will fail to compile the below
    // methods unless they appear in the class declaration BEFORE any
    // further static constants.  The reason for this behavior is unknown.
    static ::boost::large_int::large_int<T, U>
    min BOOST_PREVENT_MACRO_SUBSTITUTION () throw()
    {
        return ::boost::large_int::large_int<T, U>(
            (numeric_limits<U>::min)(),
            (numeric_limits<T>::min)());
    }
    static ::boost::large_int::large_int<T, U>
    max BOOST_PREVENT_MACRO_SUBSTITUTION () throw()
    {
        return ::boost::large_int::large_int<T, U>(
            (numeric_limits<U>::max)(),
            (numeric_limits<T>::max)());
    }
    static ::boost::large_int::large_int<T, U> epsilon() throw()
    {
        return ::boost::large_int::large_int<T, U>(T(0));
    }
    static ::boost::large_int::large_int<T, U> round_error() throw()
    {
        return ::boost::large_int::large_int<T, U>(T(0));
    }
    static ::boost::large_int::large_int<T, U> infinity() throw()
    {
        return ::boost::large_int::large_int<T, U>(T(0));
    }
    static ::boost::large_int::large_int<T, U> quiet_NaN() throw()
    {
        return ::boost::large_int::large_int<T, U>(T(0));
    }
    static ::boost::large_int::large_int<T, U> signaling_NaN() throw()
    {
        return ::boost::large_int::large_int<T, U>(T(0));
    }
    static ::boost::large_int::large_int<T, U> denorm_min() throw()
    {
        return ::boost::large_int::large_int<T, U>(T(0));
    }

    // To calculate digits10 efficiently and correctly, we use the
    // function: digits * log10(2).  However, to achieve this as a
    // constant expression we use the fraction 643/2136, which
    // approximates log10(2) to 7 significant digits.
    BOOST_STATIC_CONSTANT(int, digits = numeric_limits<U>::digits
                                      + numeric_limits<T>::digits);
    BOOST_STATIC_CONSTANT(int, digits10 = digits * 643 / 2136);
    BOOST_STATIC_CONSTANT(bool, is_signed = numeric_limits<U>::is_signed);
    BOOST_STATIC_CONSTANT(bool, is_integer = true);
    BOOST_STATIC_CONSTANT(bool, is_exact = true);
    BOOST_STATIC_CONSTANT(int, radix = 2);

    BOOST_STATIC_CONSTANT(int, min_exponent = 0);
    BOOST_STATIC_CONSTANT(int, min_exponent10 = 0);
    BOOST_STATIC_CONSTANT(int, max_exponent = 0);
    BOOST_STATIC_CONSTANT(int, max_exponent10 = 0);
    BOOST_STATIC_CONSTANT(bool, has_infinity = false);
    BOOST_STATIC_CONSTANT(bool, has_quiet_NaN = false);
    BOOST_STATIC_CONSTANT(bool, has_signaling_NaN = false);
    BOOST_STATIC_CONSTANT(float_denorm_style, has_denorm = denorm_absent);
    BOOST_STATIC_CONSTANT(bool, has_denorm_loss = false);

    BOOST_STATIC_CONSTANT(bool, is_iec559 = false);
    BOOST_STATIC_CONSTANT(bool, is_bounded = true);
    BOOST_STATIC_CONSTANT(bool, is_modulo = numeric_limits<U>::is_modulo);
    BOOST_STATIC_CONSTANT(bool, traps = numeric_limits<T>::traps);
    BOOST_STATIC_CONSTANT(bool, tinyness_before = false);
    BOOST_STATIC_CONSTANT(float_round_style, round_style = round_toward_zero);
};

} // namespace std

#endif // BOOST_LARGE_INT_LIMITS_HPP
