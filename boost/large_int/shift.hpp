// shift.hpp - Boost.LargeInt Library header file ----------------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#ifndef BOOST_LARGE_INT_SHIFT_HPP
#define BOOST_LARGE_INT_SHIFT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

#include <boost/large_int/traits.hpp> // For large_int_traits
#include <boost/large_int/cast.hpp> // For large_int_cast
#include <boost/large_int/base.hpp> // For large_int

namespace boost {
namespace large_int {

namespace detail
{
    // Private types --
    class large_int_shift_internal_t
    {
    public:
        // Utilities --
        template<class T, class U>
        static large_int<T, U> left(const large_int<T, U>& val)
        {
            // Declare types
            typedef large_int_traits<large_int<T, U> > traits;
            typedef typename traits::high_part_type hi_type;

            // Left-shift by one
            return large_int<T, U>(
                (val.m_hi << 1) | large_int_cast<hi_type>(
                    (val.m_lo >> (traits::low_bits - 1)) & 1),
                (val.m_lo << 1));
        }

        template<class T, class U>
        static large_int<T, U> right(const large_int<T, U>& val)
        {
            // Declare types
            typedef large_int_traits<large_int<T, U> > traits;
            typedef typename traits::low_part_type lo_type;

            // Right-shift by one
            return large_int<T, U>(
                (val.m_hi >> 1),
                (val.m_lo >> 1) | (large_int_cast<lo_type>(val.m_hi & 1)
                    << (traits::low_bits - 1)));
        }

        template<class T, class U>
        static large_int<T, U> left(const large_int<T, U>& val, int bits)
        {
            // Declare types
            typedef large_int_traits<large_int<T, U> > traits;
            typedef typename traits::high_part_type hi_type;
            typedef typename traits::low_part_type lo_type;

            // Take a copy of val, to modify
            large_int<T, U> ret(val);

            // Perform the left-shift
            if( bits >= traits::size_bits )
            {
                // Behavior is undefined within the C/C++ standard,
                // but GNU-gcc uses the remainder of: (bits / size_bits)
                bits %= traits::size_bits;
            }
            if( bits >= traits::high_bits )
            {
                // High part becomes zero
                ret.m_hi = 0;
            }
            if( bits >= traits::low_bits )
            {
                // Shift the entirety of the low part into
                // the least-significant bits of the high part
                bits      -= traits::low_bits;
                ret.m_hi <<= traits::low_bits % traits::high_bits;
                ret.m_hi  |= large_int_cast<hi_type>(ret.m_lo);
                ret.m_lo   = lo_type(0);
            }
            if( bits != 0 )
            {
                // Shift the high part
                ret.m_hi <<= bits;

                // Carry bits from the low part
                const lo_type mask(lo_type(~lo_type(0) << bits));
                ret.m_hi |= large_int_cast<hi_type>(
                    (ret.m_lo >> (traits::low_bits - bits)) & ~mask);

                // Shift the low part
                ret.m_lo <<= bits;
            }
            return ret;
        }

        template<class T, class U>
        static large_int<T, U> right(const large_int<T, U>& val, int bits)
        {
            // Declare types
            typedef large_int_traits<large_int<T, U> > traits;
            typedef typename traits::high_part_type hi_type;
            typedef typename traits::low_part_type lo_type;

            // Take a copy of val, to modify
            large_int<T, U> ret(val);

            // Perform the right-shift
            if( bits >= traits::size_bits )
            {
                // Behavior is undefined within the C/C++ standard,
                // but GNU-gcc uses the remainder of: (bits / size_bits)
                bits %= traits::size_bits;
            }
            if( bits >= traits::low_bits )
            {
                // Low part becomes zero
                ret.m_lo = 0;
            }
            if( bits >= traits::high_bits )
            {
                // Shift the entirety of the high part into
                // the most-significant bits of the low part
                bits      -= traits::high_bits;
                ret.m_lo >>= traits::high_bits % traits::low_bits;
                ret.m_lo  |= (traits::low_bits >= traits::high_bits)
                           ? lo_type(large_int_cast<lo_type>(ret.m_hi)
                                << ((traits::low_bits - traits::high_bits)
                                    % traits::low_bits))
                           : large_int_cast<lo_type>(ret.m_hi
                                >> ((traits::high_bits - traits::low_bits)
                                    % traits::high_bits));
                ret.m_hi   = (traits::is_neg(val))
                           ? hi_type(-1)
                           : hi_type(0);
            }
            if( bits != 0 )
            {
                // Shift the low part
                ret.m_lo >>= bits;

                // Borrow bits from the high part
                const hi_type mask(hi_type(~hi_type(0) << bits));
                ret.m_lo |= lo_type(large_int_cast<lo_type>(
                    ret.m_hi & ~mask) << (traits::low_bits - bits));

                // Shift the high part
                ret.m_hi >>= bits;
            }
            return ret;
        }
    };
} // namespace detail

// large_int_shift for all non-large_int types --
template<class T> struct large_int_shift
{
    // Utilities --
    static T left(const T& val)
    {
        return( val << 1 );
    }
    static T right(const T& val)
    {
        return( val >> 1 );
    }
    static T left(const T& val, int bits)
    {
        return( val << bits );
    }
    static T right(const T& val, int bits)
    {
        return( val >> bits );
    }
};

// large_int_shift for large_int types --
template<class T, class U> struct large_int_shift<large_int<T, U> >
{
    // Utilities --
    static large_int<T, U> left(const large_int<T, U>& val)
    {
        return detail::large_int_shift_internal_t::left<T, U>(val);
    }
    static large_int<T, U> right(const large_int<T, U>& val)
    {
        return detail::large_int_shift_internal_t::right<T, U>(val);
    }
    static large_int<T, U> left(const large_int<T, U>& val, int bits)
    {
        return detail::large_int_shift_internal_t::left<T, U>(val, bits);
    }
    static large_int<T, U> right(const large_int<T, U>& val, int bits)
    {
        return detail::large_int_shift_internal_t::right<T, U>(val, bits);
    }
};

} // namespace large_int
} // namespace boost

#endif // BOOST_LARGE_INT_SHIFT_HPP
