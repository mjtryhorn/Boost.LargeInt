// base.ipp - Boost.LargeInt Library implementation file ---------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#ifndef BOOST_LARGE_INT_IMPL_BASE_IPP
#define BOOST_LARGE_INT_IMPL_BASE_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

#include <boost/large_int/traits.hpp> // For large_int_traits
#include <boost/large_int/cast.hpp> // For large_int_cast
#include <boost/large_int/div.hpp> // For large_int_div_t, div
#include <boost/large_int/base.hpp> // For large_int

namespace boost {
namespace large_int {

// large_int methods --
template<class T, class U>
bool large_int<T, U>::operator! () const
{
    return( (! m_lo) && (! m_hi) );
}

template<class T, class U>
large_int<T, U>::operator bool_type() const
{
    // Use a pointer to member as the boolean result (safe-bool)
    return( (!(*this)) ? 0 : &this_type::safe_bool );
}

template<class T, class U>
large_int<T, U> large_int<T, U>::operator+ () const
{
    // '+' has no effect
    return *this;
}

template<class T, class U>
large_int<T, U> large_int<T, U>::operator- () const
{
    // Perform 2's compliment negation
    return( ~(*this) + this_type(1) );
}

template<class T, class U>
large_int<T, U> large_int<T, U>::operator~ () const
{
    return this_type(high_part_type(~m_hi), low_part_type(~m_lo));
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator++ ()
{
    // Take a copy of *this, to modify
    this_type ret(*this);

    // Perform the increment
    ++ret.m_lo;
    if( ret.m_lo == low_part_type(0) )
    {
        ++ret.m_hi;
    }

    // Commit the result
    return( *this = ret );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator-- ()
{
    // Take a copy of *this, to modify
    this_type ret(*this);

    // Perform the decrement
    if( ret.m_lo == low_part_type(0) )
    {
        --ret.m_hi;
    }
    --ret.m_lo;

    // Commit the result
    return( *this = ret );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator+= (const this_type& val)
{
    // Take a copy of *this, to modify
    this_type ret(*this);

    // Perform the addition
    ret.m_lo += val.m_lo;
    ret.m_hi += val.m_hi;
    if( ret.m_lo < m_lo )
    {
        ++ret.m_hi;
    }

    // Commit the result
    return( *this = ret );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator-= (const this_type& val)
{
    return( *this += -val );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator*= (const this_type& val)
{
    const this_type zero(0);
    const this_type one(1);
    this_type val_copy(val);
    this_type tmp(*this);
    this_type ret(zero);

    // Perform a bit-by-bit multiplication
    for( int i = bits; i != 0 && val_copy != zero; --i )
    {
        if( (val_copy & one) != zero )
        {
            ret += tmp;
        }

        val_copy >>= 1;
        tmp <<= 1;
    }

    // Commit the result
    return( *this = ret );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator/= (const this_type& val)
{
    return( *this = div(*this, val).quot );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator%= (const this_type& val)
{
    return( *this = div(*this, val).rem );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator|= (const this_type& val)
{
    return( *this = this_type(m_hi | val.m_hi, m_lo | val.m_lo) );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator&= (const this_type& val)
{
    return( *this = this_type(m_hi & val.m_hi, m_lo & val.m_lo) );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator^= (const this_type& val)
{
    return( *this = this_type(m_hi ^ val.m_hi, m_lo ^ val.m_lo) );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator<<= (const this_type& val)
{
    return( *this <<= large_int_cast<int>(val) );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator>>= (const this_type& val)
{
    return( *this >>= large_int_cast<int>(val) );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator<<= (int val)
{
    // Take a copy of *this, to modify
    this_type ret(*this);

    // Perform the left-shift
    if( val >= bits )
    {
        // Behavior is undefined within the C/C++ standard,
        // but GNU-gcc uses the remainder of: (val / bits)
        val %= bits;
    }
    if( val >= hibits )
    {
        // High part becomes zero
        ret.m_hi = 0;
    }
    if( val >= lobits )
    {
        // Shift the entirety of the low part into
        // the least-significant bits of the high part
        val       -= lobits;
        ret.m_hi <<= lobits % hibits;
        ret.m_hi  |= large_int_cast<high_part_type>(ret.m_lo);
        ret.m_lo   = low_part_type(0);
    }
    if( val != 0 )
    {
        // Shift the high part
        ret.m_hi <<= val;

        // Carry bits from the low part
        const low_part_type mask(low_part_type(~low_part_type(0) << val));
        ret.m_hi |= large_int_cast<high_part_type>(
            (ret.m_lo >> (lobits - val)) & ~mask);

        // Shift the low part
        ret.m_lo <<= val;
    }

    // Commit the result
    return( *this = ret );
}

template<class T, class U>
large_int<T, U>& large_int<T, U>::operator>>= (int val)
{
    // Take a copy of *this, to modify
    this_type ret(*this);

    // Perform the right-shift
    if( val >= bits )
    {
        // Behavior is undefined within the C/C++ standard,
        // but GNU-gcc uses the remainder of: (val / bits)
        val %= bits;
    }
    if( val >= lobits )
    {
        // Low part becomes zero
        ret.m_lo = 0;
    }
    if( val >= hibits )
    {
        // Shift the entirety of the high part into
        // the most-significant bits of the low part
        val       -= hibits;
        ret.m_lo >>= hibits % lobits;
        ret.m_lo  |= (lobits >= hibits)
                   ? low_part_type(large_int_cast<low_part_type>(ret.m_hi)
                                   << ((lobits - hibits) % lobits))
                   : large_int_cast<low_part_type>(
                       ret.m_hi >> ((hibits - lobits) % hibits));
        ret.m_hi   = (large_int_traits<this_type>::is_neg(*this))
                   ? high_part_type(-1)
                   : high_part_type(0);
    }
    if( val != 0 )
    {
        // Shift the low part
        ret.m_lo >>= val;

        // Borrow bits from the high part
        const high_part_type mask(high_part_type(~high_part_type(0) << val));
        ret.m_lo |= low_part_type(large_int_cast<low_part_type>(
            ret.m_hi & ~mask) << (lobits - val));

        // Shift the high part
        ret.m_hi >>= val;
    }

    // Commit the result
    return( *this = ret );
}

// Comparison operators --
template<class T1, class U1, class T2, class U2>
bool operator< (const large_int<T1, U1>& lhs, const large_int<T2, U2>& rhs)
{
    return large_int_traits<large_int<T1, U1> >::lt(lhs, rhs);
}

template<class T1, class U1, class T2, class U2>
bool operator<= (const large_int<T1, U1>& lhs, const large_int<T2, U2>& rhs)
{
    return( !(rhs < lhs) );
}

template<class T1, class U1, class T2, class U2>
bool operator== (const large_int<T1, U1>& lhs, const large_int<T2, U2>& rhs)
{
    return large_int_traits<large_int<T1, U1> >::eq(lhs, rhs);
}

template<class T1, class U1, class T2, class U2>
bool operator!= (const large_int<T1, U1>& lhs, const large_int<T2, U2>& rhs)
{
    return( !(lhs == rhs) );
}

template<class T1, class U1, class T2, class U2>
bool operator>= (const large_int<T1, U1>& lhs, const large_int<T2, U2>& rhs)
{
    return( !(lhs < rhs) );
}

template<class T1, class U1, class T2, class U2>
bool operator> (const large_int<T1, U1>& lhs, const large_int<T2, U2>& rhs)
{
    return( rhs < lhs );
}

template<class T, class U>
bool operator< (const large_int<T, U>& lhs, long rhs)
{
    return large_int_traits<large_int<T, U> >::lt_literal(lhs, rhs);
}

template<class T, class U>
bool operator<= (const large_int<T, U>& lhs, long rhs)
{
    return( (lhs < rhs) || (lhs == rhs) );
}

template<class T, class U>
bool operator== (const large_int<T, U>& lhs, long rhs)
{
    return large_int_traits<large_int<T, U> >::eq_literal(lhs, rhs);
}

template<class T, class U>
bool operator!= (const large_int<T, U>& lhs, long rhs)
{
    return( !(lhs == rhs) );
}

template<class T, class U>
bool operator>= (const large_int<T, U>& lhs, long rhs)
{
    return( !(lhs < rhs) );
}

template<class T, class U>
bool operator> (const large_int<T, U>& lhs, long rhs)
{
    return( !((lhs < rhs) || (lhs == rhs)) );
}

template<class T, class U>
bool operator< (long lhs, const large_int<T, U>& rhs)
{
    return( rhs > lhs );
}

template<class T, class U>
bool operator<= (long lhs, const large_int<T, U>& rhs)
{
    return( rhs >= lhs );
}

template<class T, class U>
bool operator== (long lhs, const large_int<T, U>& rhs)
{
    return( rhs == lhs );
}

template<class T, class U>
bool operator!= (long lhs, const large_int<T, U>& rhs)
{
    return( rhs != lhs );
}

template<class T, class U>
bool operator>= (long lhs, const large_int<T, U>& rhs)
{
    return( rhs <= lhs );
}

template<class T, class U>
bool operator> (long lhs, const large_int<T, U>& rhs)
{
    return( rhs < lhs );
}

} // namespace large_int
} // namespace boost

#endif // BOOST_LARGE_INT_IMPL_BASE_IPP
