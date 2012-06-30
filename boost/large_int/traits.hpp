// traits.hpp - Boost.LargeInt Library header file ---------------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#ifndef BOOST_LARGE_INT_TRAITS_HPP
#define BOOST_LARGE_INT_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

#include <boost/limits.hpp> // For std::numeric_limits
#include <boost/config.hpp> // For BOOST_STATIC_CONSTANT
#include <boost/type_traits/is_same.hpp> // For boost::is_same
#include <boost/type_traits/integral_constant.hpp> // For boost::true_type,
                                                   // boost::false_type,
                                                   // boost::integral_constant
#include <boost/large_int/base.hpp> // For large_int
#include <boost/large_int/limits.hpp>
    // For std::numeric_limits<large_int<T,U> >

namespace boost {
namespace large_int {

namespace detail
{
    // Private types --
    class large_int_traits_internal_t
    {
    private:
        // Private utilities --
        template<class T, class U>
        static const U& promote_if(const U& val, const boost::false_type&)
        {
            return val; // Do not alter the given value
        }
        template<class T, class U>
        static T promote_if(const U& val, const boost::true_type&)
        {
            return T(val); // Promote the given value
        }

        static large_int<unsigned long, unsigned int> promote_literal(
            unsigned long v, const boost::false_type& /*is_signed*/)
        {
            // Construct a new large_int value from the unsigned source
            return large_int<unsigned long, unsigned int>(v);
        }
        static large_int<unsigned long, int> promote_literal(
            long v, const boost::true_type& /*is_signed*/)
        {
            // Construct a new large_int value from the signed source
            return large_int<unsigned long, int>(v);
        }

        template<class T, class U>
        static bool lt_internal(const large_int<T, U>& lhs,
                                const large_int<T, U>& rhs,
                                const boost::true_type& /*is_same*/)
        {
            return (lhs.m_hi == rhs.m_hi)
                ? (lhs.m_lo < rhs.m_lo)  // Compare low parts
                : (lhs.m_hi < rhs.m_hi); // Compare high parts
        }
        template<class T1, class U1, class T2, class U2>
        static bool lt_internal(const large_int<T1, U1>& lhs,
                                const large_int<T2, U2>& rhs,
                                const boost::false_type& /*is_same*/)
        {
            // Declare types
            typedef large_int<T1, U1> lhs_type;
            typedef large_int<T2, U2> rhs_type;
            typedef std::numeric_limits<lhs_type> lhs_limits;
            typedef std::numeric_limits<rhs_type> rhs_limits;

            // Promote either 'lhs' to 'rhs_type' or 'rhs' to 'lhs_type'
            // depending upon whichever is the larger integral type.
            return lt_internal(
                promote_if<rhs_type>(lhs, boost::integral_constant<bool,
                    (lhs_limits::digits < rhs_limits::digits)>()),
                promote_if<lhs_type>(rhs, boost::integral_constant<bool,
                    (lhs_limits::digits >= rhs_limits::digits)>()),
                boost::true_type());
        }

        template<class T, class U>
        static bool eq_internal(const large_int<T, U>& lhs,
                                const large_int<T, U>& rhs,
                                const boost::true_type& /*is_same*/)
        {
            // Compare high and low parts indiscriminately
            return( (lhs.m_hi == rhs.m_hi) && (lhs.m_lo == rhs.m_lo) );
        }
        template<class T1, class U1, class T2, class U2>
        static bool eq_internal(const large_int<T1, U1>& lhs,
                                const large_int<T2, U2>& rhs,
                                const boost::false_type& /*is_same*/)
        {
            // Declare types
            typedef large_int<T1, U1> lhs_type;
            typedef large_int<T2, U2> rhs_type;
            typedef std::numeric_limits<lhs_type> lhs_limits;
            typedef std::numeric_limits<rhs_type> rhs_limits;

            // Promote either 'lhs' to 'rhs_type' or 'rhs' to 'lhs_type'
            // depending upon whichever is the larger integral type.
            return eq_internal(
                promote_if<rhs_type>(lhs, boost::integral_constant<bool,
                    (lhs_limits::digits < rhs_limits::digits)>()),
                promote_if<lhs_type>(rhs, boost::integral_constant<bool,
                    (lhs_limits::digits >= rhs_limits::digits)>()),
                boost::true_type());
        }

        template<class T, class U>
        static bool is_neg_internal(const large_int<T, U>& /*val*/,
                                    const boost::false_type& /*is_signed*/)
        {
            return false;
        }
        template<class T, class U>
        static bool is_neg_internal(const large_int<T, U>& val,
                                    const boost::true_type& /*is_signed*/)
        {
            return lt(val, large_int<T, U>(0));
        }

    public:
        // Utilities --
        // Note that all promotions of literal values to large_ints in
        // the below methods will automatically match rhs's signed state
        // to the signed state of lhs (the large_int value).  This is
        // necessary as defining both signed and unsigned versions of
        // operator< and operator== for literal values produces ambiguity
        // errors when promoting non-long literal rhs types.  Also, note
        // that performing comparisons between unsigned and signed values
        // would normally produce a warning, and should be avoided.
        template<class T1, class U1, class T2, class U2>
        static bool lt(const large_int<T1, U1>& lhs,
                       const large_int<T2, U2>& rhs)
        {
            // Perform a less-than comparison, promoting one of the
            // two given values if their types are not an exact match
            return lt_internal(lhs, rhs, boost::is_same
                <large_int<T1, U1>, large_int<T2, U2> >());
        }

        template<class T1, class U1, class T2, class U2>
        static bool eq(const large_int<T1, U1>& lhs,
                       const large_int<T2, U2>& rhs)
        {
            // Perform an equal-to comparison, promoting one of the
            // two given values if their types are not an exact match
            return eq_internal(lhs, rhs, boost::is_same
                <large_int<T1, U1>, large_int<T2, U2> >());
        }

        template<class T, class U>
        static bool lt_literal(const large_int<T, U>& lhs, long rhs)
        {
            return lt(lhs, promote_literal(rhs, boost::integral_constant<
                bool, std::numeric_limits<large_int<T, U> >::is_signed>()));
        }

        template<class T, class U>
        static bool eq_literal(const large_int<T, U>& lhs, long rhs)
        {
            return eq(lhs, promote_literal(rhs, boost::integral_constant<
                bool, std::numeric_limits<large_int<T, U> >::is_signed>()));
        }

        template<class T, class U>
        static bool is_neg(const large_int<T, U>& val)
        {
            return is_neg_internal(val, boost::integral_constant<bool,
                std::numeric_limits<large_int<T, U> >::is_signed>());
        }

        template<class T, class U>
        static bool is_zero(const large_int<T, U>& val)
        {
            // Compare high and low parts indiscriminately
            return( (val.m_hi == U(0)) && (val.m_lo == T(0)) );
        }
    };
} // namespace detail

// large_int_traits for all non-large_int types --
template<class T> struct large_int_traits
{
    BOOST_STATIC_CONSTANT(bool, is_large_int = false);
};

// large_int_traits for large_int types --
template<class T, class U> struct large_int_traits<large_int<T, U> >
{
public:
    // Types --
    typedef T low_part_type;
    typedef U high_part_type;

    // Constants --
    BOOST_STATIC_CONSTANT(bool, is_large_int = true);
    BOOST_STATIC_CONSTANT(int, low_bits = std::numeric_limits<T>::digits);
    BOOST_STATIC_CONSTANT(int, high_bits = std::numeric_limits<U>::digits
                                         + std::numeric_limits<U>::is_signed);
    BOOST_STATIC_CONSTANT(int, size_bits = low_bits + high_bits);

    // Utilities --
    template<class T2, class U2>
    static bool lt(const large_int<T, U>& lhs,
                   const large_int<T2, U2>& rhs)
    {
        return detail::large_int_traits_internal_t::lt<T, U, T2, U2>(
            lhs, rhs);
    }
    template<class T2, class U2>
    static bool eq(const large_int<T, U>& lhs,
                   const large_int<T2, U2>& rhs)
    {
        return detail::large_int_traits_internal_t::eq<T, U, T2, U2>(
            lhs, rhs);
    }
    static bool lt_literal(const large_int<T, U>& lhs, long rhs)
    {
        return detail::large_int_traits_internal_t::lt_literal<T, U>(
            lhs, rhs);
    }
    static bool eq_literal(const large_int<T, U>& lhs, long rhs)
    {
        return detail::large_int_traits_internal_t::eq_literal<T, U>(
            lhs, rhs);
    }
    static bool is_neg(const large_int<T, U>& val)
    {
        return detail::large_int_traits_internal_t::is_neg<T, U>(val);
    }
    static bool is_zero(const large_int<T, U>& val)
    {
        return detail::large_int_traits_internal_t::is_zero<T, U>(val);
    }
};

} // namespace large_int
} // namespace boost

#endif // BOOST_LARGE_INT_TRAITS_HPP
