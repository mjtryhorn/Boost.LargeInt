// div.hpp - Boost.LargeInt Library header file ------------------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#ifndef BOOST_LARGE_INT_DIV_HPP
#define BOOST_LARGE_INT_DIV_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

#include <stdexcept> // For std::domain_error
#include <boost/static_assert.hpp> // For BOOST_STATIC_ASSERT
#include <boost/throw_exception.hpp> // For BOOST_THROW_EXCEPTION
#include <boost/large_int/base.hpp> // For large_int
#include <boost/large_int/traits.hpp> // For large_int_traits
#include <boost/large_int/shift.hpp> // For large_int_shift
#include <boost/large_int/utils.hpp> // For abs

namespace boost {
namespace large_int {

namespace detail
{
    // Private types --
    class large_int_div_internal_t
    {
    public:
        // Utilities --
        template<class T, class U>
        static large_int_div_t<large_int<T, U> > do_divide(
            const large_int<T, U>& numerator,
            const large_int<T, U>& denominator);
    };

    // large_int_div_internal_t methods --
    template<class T, class U>
    large_int_div_t<large_int<T, U> >
    large_int_div_internal_t::do_divide(const large_int<T, U>& numerator,
                                        const large_int<T, U>& denominator)
    {
        // Declare constants & variables
        typedef large_int<T, U> value_type;
        typedef large_int_traits<value_type> value_traits_type;
        const value_type zero(0);
        const value_type one(1);
        value_type denom_tmp(denominator);
        bool is_quot_neg(false);
        bool is_rem_neg(false);
        large_int_div_t<value_type> result(numerator, zero);

        // Check for divison by zero
        if( ! denominator )
        {
            // Attempt to trigger a division by zero signal (SIGFPE),
            // or throw an exception if no such signal is supported
            denom_tmp.m_lo = numerator.m_lo / denominator.m_lo;
            BOOST_THROW_EXCEPTION(std::domain_error(
                "large_int: division by zero"));
        }

        // Check for negative results
        if( value_traits_type::is_neg(result.quot) ||
            value_traits_type::is_neg(denom_tmp) )
        {
            is_quot_neg = value_traits_type::is_neg(result.quot)
                       != value_traits_type::is_neg(denom_tmp);
            is_rem_neg  = value_traits_type::is_neg(result.quot);

            // Convert the quotient and denominator to positive
            // equivalents, to simplify the division calculation
            result.quot = abs(result.quot);
            denom_tmp   = abs(denom_tmp);
        }

        // Perform the division
        for( int i = value_type::bits; i != 0; --i )
        {
            result.rem  = large_int_shift<value_type>::left(result.rem);
            result.rem |= (result.quot >> (value_type::bits - 1)) & one;
            result.quot = large_int_shift<value_type>::left(result.quot);

            if( is_quot_neg | is_rem_neg )
            {
                if( value_traits_type::eq(result.rem, denom_tmp) ||
                    value_traits_type::lt(-result.rem, -denom_tmp) )
                {
                    result.rem  -= denom_tmp;
                    result.quot |= one;
                }
            }
            else
            {
                if( value_traits_type::eq(denom_tmp, result.rem) ||
                    value_traits_type::lt(denom_tmp, result.rem) )
                {
                    result.rem  -= denom_tmp;
                    result.quot |= one;
                }
            }
        }

        // Negate the results as appropriate
        if( is_quot_neg )
        {
            result.quot = -result.quot;
        }
        if( is_rem_neg )
        {
            result.rem = -result.rem;
        }
        return result;
    }
} // namespace detail

// Public types & functions --
template<class T> struct large_int_div_t
{
    // Type 'T' is not a large_int based type
    BOOST_STATIC_ASSERT(sizeof( T ) == 0);
};

template<class T, class U> struct large_int_div_t<large_int<T, U> >
{
    // Values --
    large_int<T, U> quot; // The quotient
    large_int<T, U> rem; // The remainder

    // Constructor --
    explicit large_int_div_t(
        const large_int<T, U>& quot_in = (large_int<T, U>()),
        const large_int<T, U>& rem_in = (large_int<T, U>()))
        : quot(quot_in), rem(rem_in) { }
};

template<class T, class U> large_int_div_t<large_int<T, U> > div(
    const large_int<T,U>& numerator, const large_int<T,U>& denominator)
{
    return detail::large_int_div_internal_t::do_divide(numerator,
                                                       denominator);
}

} // namespace large_int
} // namespace boost

#endif // BOOST_LARGE_INT_DIV_HPP
