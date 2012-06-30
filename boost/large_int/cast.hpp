// cast.hpp - Boost.LargeInt Library header file -----------------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#ifndef BOOST_LARGE_INT_CAST_HPP
#define BOOST_LARGE_INT_CAST_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

#include <boost/limits.hpp> // For std::numeric_limits
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
    template<class T> class large_int_cast_t
    {
    public:
        // Utilities --
        template<class C> static C do_cast(const T& val)
        {
            // 'val' is not a large_int value - perform a normal cast
            return static_cast<C>(val);
        }
    };

    template<class T, class U> class large_int_cast_t<large_int<T, U> >
    {
    private:
        // Private utilities --
        template<class C> static C cast_internal(const large_int<T, U>& val,
            const boost::false_type& /*low_part_overflow*/)
        {
            // Convert the large_int's low part only
            return large_int_cast_t<T>::template do_cast<C>(val.m_lo);
        }
        template<class C> static C cast_internal(const large_int<T, U>& val,
            const boost::true_type& /*low_part_overflow*/)
        {
            // Build the result from both the large_int's low and high parts
            C result(large_int_cast_t<U>::template do_cast<C>(val.m_hi));
            result <<= std::numeric_limits<T>::digits;
            result  |= large_int_cast_t<T>::template do_cast<C>(val.m_lo);
            return result;
        }

    public:
        // Utilities --
        template<class C> static C do_cast(const large_int<T, U>& val)
        {
            // 'val' is a large_int - perform a special cast
            typedef std::numeric_limits<C> c_limits;
            typedef std::numeric_limits<T> low_limits;
            return cast_internal<C>(val,
                boost::integral_constant<bool, (low_limits::digits
                    < (c_limits::digits + c_limits::is_signed))>());
        }
    };
} // namespace detail

// Public functions --
template<class C, class T> C large_int_cast(const T& val)
{
    return detail::large_int_cast_t<T>::template do_cast<C>(val);
}

} // namespace large_int
} // namespace boost

#endif // BOOST_LARGE_INT_CAST_HPP
