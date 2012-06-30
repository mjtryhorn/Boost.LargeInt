// utils.hpp - Boost.LargeInt Library header file ----------------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#ifndef BOOST_LARGE_INT_UTILS_HPP
#define BOOST_LARGE_INT_UTILS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

#include <string> // For std::char_traits
#include <stdexcept> // For std::invalid_argument
#include <boost/static_assert.hpp> // For BOOST_STATIC_ASSERT
#include <boost/throw_exception.hpp> // For BOOST_THROW_EXCEPTION
#include <boost/large_int/base.hpp> // For large_int
#include <boost/large_int/traits.hpp> // For large_int_traits

namespace boost {
namespace large_int {

// Namespace functions --
template<class T, class U>
large_int<T, U> abs(const large_int<T, U>& val)
{
    return( large_int_traits<large_int<T, U> >::is_neg(val) ? -val : val );
}

template<class T, class CharT>
T make_large_int(const CharT* s)
{
    typedef std::char_traits<CharT> traits_type;
    const CharT* s_end(&s[traits_type::length(s)]);
    return make_large_int<T>(s, s_end);
}

template<class T, class InputIterator>
T make_large_int(InputIterator first, InputIterator last, int base)
{
    T result;
    if( make_large_int<T>(first, last, base, result) != last )
    {
        // Not all digits were consumed - one or more must be invalid
        BOOST_THROW_EXCEPTION(std::invalid_argument(
            "large_int: number contains one or more invalid digits"));
    }
    return result;
}

template<class T, class InputIterator>
InputIterator make_large_int(InputIterator first,
                             InputIterator last,
                             int base,
                             T& result)
{
    // Check that type 'T' is a large_int based type
    BOOST_STATIC_ASSERT(large_int_traits<T>::is_large_int);

    // Create a temporary result, initialised to zero
    bool valid(false);
    T tmp_result(0);

    // If a non-zero-length sequence is given...
    if( first != last )
    {
        // Check for a numeric prefix
        bool is_neg(false);
        switch( *first )
        {
            case '+': // Positive decimal number
                base = 10;
                ++first;
                break;
            case '-': // Negative decimal number
                is_neg = true;
                base = 10;
                ++first;
                break;
            case '0': // Possible hex/octal number
                ++first;
                if( first != last && (*first == 'x' || *first == 'X') )
                {
                    // Hexadecimal number
                    base = 16;
                    ++first;
                }
                else
                {
                    // Octal number (or zero)
                    base = 8;
                    valid = true;
                }
                break;
            default: // Default to decimal
                if( base == 0 )
                {
                    base = 10;
                }
                break;
        }

        // Extract all digits
        const T large_base(base);
        for( int n; first != last; ++first )
        {
            // Extract the next digit and check that it is valid
            n = (*first >= 'a') ? (*first - ('a' - 0xa)) // Lowercase hex
              : (*first >= 'A') ? (*first - ('A' - 0xa)) // Uppercase hex
              : (*first - '0'); // Decimal
            if( n < 0 || n >= base )
            {
                // Next digit is out of range for the base
                break;
            }

            // Insert the next digit into the result
            tmp_result *= large_base;
            tmp_result += T(n);
            valid = true;
        }

        // Negate the result as appropriate
        if( is_neg )
        {
            tmp_result = -tmp_result;
        }
    }

    // Check that at least one valid digit was found
    if( ! valid )
    {
        BOOST_THROW_EXCEPTION(std::invalid_argument(
            "large_int: number contains no valid digits"));
    }

    // Copy the temporary result over the actual result then
    // return an iterator to the position at which the integer ends
    result = tmp_result;
    return first;
}

} // namespace large_int
} // namespace boost

#endif // BOOST_LARGE_INT_UTILS_HPP
