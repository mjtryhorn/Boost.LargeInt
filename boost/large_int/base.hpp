// base.hpp - Boost.LargeInt Library header file -----------------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#ifndef BOOST_LARGE_INT_BASE_HPP
#define BOOST_LARGE_INT_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

#include <boost/limits.hpp> // For std::numeric_limits
#include <boost/config.hpp> // For BOOST_STATIC_CONSTANT
#include <boost/operators.hpp> // For boost operator helpers
#include <boost/static_assert.hpp> // For BOOST_STATIC_ASSERT
#include <boost/type_traits/integral_constant.hpp> // For boost::true_type,
                                                   // boost::false_type,
                                                   // boost::integral_constant
#include <boost/type_traits/ice.hpp> // For boost::type_traits::ice_and,
                                     //     boost::type_traits::ice_not,
                                     //     boost::type_traits::ice_eq
#include <boost/large_int/fwd.hpp> // For detail::large_int_cast_t,
                              //     detail::large_int_compare_t,
                              //     detail::large_int_div_internal_t,
                              //     detail::large_int_traits_internal_t
#include <boost/large_int/limits.hpp>
    // For std::numeric_limits<large_int<T,U> >
#include <boost/large_int/cast.hpp> // For large_int_cast

namespace boost {
namespace large_int {

// Types --
template<class T, class U>
class large_int
    : boost::integer_arithmetic<large_int<T, U> >
    , boost::bitwise<large_int<T, U> >
    , boost::unit_steppable<large_int<T, U> >
    , boost::shiftable<large_int<T, U> >
    , boost::shiftable<large_int<T, U>, int>
{
private:
    // Type 'T' (low_part_type) must be an unsigned integral type --
    BOOST_STATIC_ASSERT((boost::type_traits::ice_and<
        std::numeric_limits<T>::is_exact,
        std::numeric_limits<T>::is_modulo,
        std::numeric_limits<T>::is_bounded,
        std::numeric_limits<T>::is_integer,
        boost::type_traits::ice_eq<std::numeric_limits<T>::radix, 2>::value,
        boost::type_traits::ice_not<std::numeric_limits<T>::is_signed>::value>
    ::value));

    // Type 'U' (high_part_type) must be a signed or unsigned integral type --
    BOOST_STATIC_ASSERT((boost::type_traits::ice_and<
        std::numeric_limits<U>::is_exact,
        std::numeric_limits<U>::is_bounded,
        std::numeric_limits<U>::is_integer,
        boost::type_traits::ice_eq<std::numeric_limits<U>::radix, 2>::value>
    ::value));

    // Constants --
    BOOST_STATIC_CONSTANT(int, lobits = std::numeric_limits<T>::digits);
    BOOST_STATIC_CONSTANT(int, hibits = std::numeric_limits<U>::digits
                                      + std::numeric_limits<U>::is_signed);
    BOOST_STATIC_CONSTANT(int, bits = hibits + lobits);

    // Types --
    typedef large_int<T, U> this_type;
    typedef T low_part_type;
    typedef U high_part_type;
    typedef void (this_type::*bool_type)() const;

    // Internal values --
    low_part_type m_lo;
    high_part_type m_hi;

    // Private utilities --
    template<class Value> static high_part_type to_high_part(
        const Value&, const boost::false_type& /*low_part_overflow*/,
        const boost::false_type& /*value_is_signed*/)
    {
        // Value is unsigned and smaller than (or equal to) low_part.
        // High part defaults to zero.
        return 0;
    }
    template<class Value> static high_part_type to_high_part(
        const Value& val, const boost::false_type& /*low_part_overflow*/,
        const boost::true_type& /*value_is_signed*/)
    {
        // Value is signed and smaller than (or equal to) low_part.
        // High part defaults to either 0 or -1 depending on val's sign.
        return high_part_type((val < Value(0)) ? -1 : 0);
    }
    template<class Value, bool b> static high_part_type to_high_part(
        const Value& val, const boost::true_type& /*low_part_overflow*/,
        const boost::integral_constant<bool, b>& /*value_is_signed*/)
    {
        // Value is signed or unsigned and larger than low_part.
        // Copy bits from value 'val' into the new high part.
        return large_int_cast<high_part_type>(
            val >> static_cast<int>(lobits));
    }
    template<class Value> static high_part_type to_high_part(const Value& val)
    {
        // Calculate the initial high part according to whether the given
        // value is or is not signed, and whether it exceeds lobits
        typedef std::numeric_limits<Value> value_limits;
        return to_high_part(val,
            boost::integral_constant<bool, (value_limits::digits > lobits)>(),
            boost::integral_constant<bool, value_limits::is_signed>());
    }

    // Safe-bool member function --
    void safe_bool() const { /* empty */ }

    // Friends --
    template<class V> friend class detail::large_int_cast_t;
    friend class detail::large_int_traits_internal_t;
    friend class detail::large_int_shift_internal_t;
    friend class detail::large_int_div_internal_t;

public:
    // Logical operators --
    bool operator! () const;
    operator bool_type() const;

    // Artithmetic operators --
    this_type operator+ () const;
    this_type operator- () const;
    this_type operator~ () const;
    this_type& operator++ ();
    this_type& operator-- ();
    this_type& operator+= (const this_type& val);
    this_type& operator-= (const this_type& val);
    this_type& operator*= (const this_type& val);
    this_type& operator/= (const this_type& val);
    this_type& operator%= (const this_type& val);

    // Bitwise operators --
    this_type& operator|= (const this_type& val);
    this_type& operator&= (const this_type& val);
    this_type& operator^= (const this_type& val);

    // Shift operators --
    this_type& operator<<= (const this_type& val);
    this_type& operator>>= (const this_type& val);
    this_type& operator<<= (int val);
    this_type& operator>>= (int val);

    // Constructors --
    explicit large_int(const T& lo = T()) : m_lo(lo), m_hi() { }
    large_int(const U& hi, const T& lo) : m_lo(lo), m_hi(hi) { }
    template<class Value> large_int(const Value& val)
        : m_lo(large_int_cast<low_part_type>(val))
        , m_hi(to_high_part(val)) { }
};

} // namespace large_int
} // namespace boost

#endif // BOOST_LARGE_INT_BASE_HPP
