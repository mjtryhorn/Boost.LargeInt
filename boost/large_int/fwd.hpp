// fwd.hpp - Boost.LargeInt Library header file ------------------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#ifndef BOOST_LARGE_INT_FWD_HPP
#define BOOST_LARGE_INT_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

#include <iosfwd> // For std::basic_istream, std::basic_ostream

namespace boost {
namespace large_int {

namespace detail
{
    // Private types --
    template<class T> class large_int_cast_t;
    class large_int_traits_internal_t;
    class large_int_div_internal_t;
} // namespace detail

// Types --
template<class T, class U> class large_int;
template<class T> struct large_int_traits;
template<class T> struct large_int_div_t;

// Mathematical functions --
template<class C, class T> C large_int_cast(const T& val);
template<class T, class U> large_int<T, U> abs(const large_int<T, U>&);
template<class T, class U> large_int_div_t<large_int<T, U> > div(
    const large_int<T, U>& numerator,
    const large_int<T, U>& denominator);

// Creation functions --
template<class T, class CharT> T make_large_int(const CharT* s);
template<class T, class InputIterator> T make_large_int(
    InputIterator first, InputIterator last, int base = 0);
template<class T, class InputIterator> InputIterator make_large_int(
    InputIterator first, InputIterator last, int base, T& result);

// Comparison operators (for large_int types) --
template<class T1, class U1, class T2, class U2> bool operator<
    (const large_int<T1, U1>&, const large_int<T2, U2>&);
template<class T1, class U1, class T2, class U2> bool operator<=
    (const large_int<T1, U1>&, const large_int<T2, U2>&);
template<class T1, class U1, class T2, class U2> bool operator==
    (const large_int<T1, U1>&, const large_int<T2, U2>&);
template<class T1, class U1, class T2, class U2> bool operator!=
    (const large_int<T1, U1>&, const large_int<T2, U2>&);
template<class T1, class U1, class T2, class U2> bool operator>=
    (const large_int<T1, U1>&, const large_int<T2, U2>&);
template<class T1, class U1, class T2, class U2> bool operator>
    (const large_int<T1, U1>&, const large_int<T2, U2>&);

// Comparison operators (for builtin integer types) --
// (These implement support of comparison against literal constants.)
template<class T, class U> bool operator< (const large_int<T, U>&, long);
template<class T, class U> bool operator<= (const large_int<T, U>&, long);
template<class T, class U> bool operator== (const large_int<T, U>&, long);
template<class T, class U> bool operator!= (const large_int<T, U>&, long);
template<class T, class U> bool operator>= (const large_int<T, U>&, long);
template<class T, class U> bool operator> (const large_int<T, U>&, long);

template<class T, class U> bool operator< (long, const large_int<T, U>&);
template<class T, class U> bool operator<= (long, const large_int<T, U>&);
template<class T, class U> bool operator== (long, const large_int<T, U>&);
template<class T, class U> bool operator!= (long, const large_int<T, U>&);
template<class T, class U> bool operator>= (long, const large_int<T, U>&);
template<class T, class U> bool operator> (long, const large_int<T, U>&);

// Streaming operators --
template<class CharT, class Traits, class T, class U>
std::basic_istream<CharT, Traits>& operator>> (
    std::basic_istream<CharT, Traits>& i,
    large_int<T, U>& val);
template<class CharT, class Traits, class T, class U>
std::basic_ostream<CharT, Traits>& operator<< (
    std::basic_ostream<CharT, Traits>& o,
    const large_int<T, U>& val);

} // namespace large_int
} // namespace boost

#endif // BOOST_LARGE_INT_FWD_HPP
