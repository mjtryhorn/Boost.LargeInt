// io.hpp - Boost.LargeInt Library header file -------------------------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#ifndef BOOST_LARGE_INT_IO_HPP
#define BOOST_LARGE_INT_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

#include <ios> // For std::ios_base
#include <istream> // For std::basic_istream
#include <ostream> // For std::basic_ostream
#include <stdexcept> // For std::invalid_argument
#include <iterator> // For std::istreambuf_iterator
#include <locale> // For std::ctype, std::locale, std::use_facet
#include <boost/config.hpp> // For BOOST_STATIC_CONSTANT
#include <boost/large_int/base.hpp> // For large_int
#include <boost/large_int/traits.hpp> // For large_int_traits
#include <boost/large_int/utils.hpp> // For abs, make_large_int
#include <boost/large_int/div.hpp> // For div, large_int_div_t

namespace boost {
namespace large_int {

// Namespace operators --
template<class CharT, class Traits, class T, class U>
std::basic_istream<CharT, Traits>& operator>> (
    std::basic_istream<CharT, Traits>& i,
    large_int<T, U>& val)
{
    // Convert the stream's flags to a base value
    const std::ios_base::fmtflags flags(i.flags());
    const int base = (flags & std::ios_base::oct) ? 8  // Octal
                   : (flags & std::ios_base::dec) ? 10 // Decimal
                   : (flags & std::ios_base::hex) ? 16 // Hexadecimal
                   : 0; // Unspecified

    // Create iterators for the given stream and
    // skip any leading whitespace as appropriate
    std::istreambuf_iterator<CharT> last, first(i);
    if( flags & std::ios_base::skipws )
    {
        // Use the default locale and character type's facet
        // directly rather than through std::isspace, for portability.
        typedef std::ctype<CharT> facet_type;
        const facet_type& char_facet(std::use_facet<facet_type>(
            std::locale()));
        while( first != last && char_facet.is(facet_type::space, *first) )
        {
            ++first;
        }
    }

    try
    {
        // Attempt to read a large_int from the given input stream
        make_large_int(first, last, base, val);
    }
    catch( std::invalid_argument& )
    {
        // Convert this exception to an alteration of the stream's state,
        // as would occur when attempting to read into a built-in integer.
        i.setstate(std::ios_base::failbit);
    }
    return i;
}

template<class CharT, class Traits, class T, class U>
std::basic_ostream<CharT, Traits>& operator<< (
    std::basic_ostream<CharT, Traits>& o,
    const large_int<T, U>& val)
{
    // Declare types and calculate the maximum length (in characters) of any
    // input large_int value (for the given template parameters), allowing for
    // an optional '0', '0x' or '0X' numeric prefix and a null-terminator.
    typedef large_int<T, U> value_type;
    typedef large_int_div_t<value_type> value_div_type;
    typedef large_int_traits<value_type> value_traits_type;
    BOOST_STATIC_CONSTANT(int, size_bits = value_traits_type::size_bits);
    BOOST_STATIC_CONSTANT(int, val_maxlen = ((size_bits + 2) / 3) + 1);

    // Construct a temporary string buffer of the calculated maximum length
    // and a position pointer, initially pointed to this buffer's end.  The
    // integer string will be constructed from its end towards its beginning.
    const char hex_digits_lc[] = "0123456789abcdefx";
    const char hex_digits_uc[] = "0123456789ABCDEFX";
    char val_str[val_maxlen + 1];
    char* val_pos(&val_str[val_maxlen]);

    // Initialise the result string to empty
    *val_pos = '\0';

    // If the given value is zero, then it should be
    // printed as "0", with no base and no sign information
    if( value_traits_type::is_zero(val) )
    {
        *(--val_pos) = '0';
    }
    else
    {
        // Choose an appropriate base and character set
        const std::ios_base::fmtflags flags(o.flags());
        const int base = (flags & std::ios_base::oct) ? 8  // Octal
                       : (flags & std::ios_base::hex) ? 16 // Hexadecimal
                       : 10; // Decimal (default)
        const char* const digits = (flags & std::ios_base::uppercase)
                                 ? &hex_digits_uc[0]  // Uppercase output
                                 : &hex_digits_lc[0]; // Lowercase output

        // Write the number, in reverse, into the string buffer
        switch( base )
        {
            case 8:
            {
                // Print the input integer, unsigned, in octal
                const value_type mask(base - 1);
                value_type val_copy(val);
                int i = size_bits;
                while( i >= 3 && ! value_traits_type::is_zero(val_copy) )
                {
                    // Print the next digit
                    *(--val_pos) = digits[large_int_cast<int>(
                        val_copy & mask)];
                    val_copy >>= 3;
                    i -= 3;
                }
                if( i != 0 && ! value_traits_type::is_zero(val_copy) )
                {
                    // Print the final digit
                    *(--val_pos) = digits[large_int_cast<int>(
                        val_copy & (mask >> (3 - i)))];
                }

                // Prepend an octal prefix, if requested
                if( flags & std::ios_base::showbase )
                {
                    *(--val_pos) = digits[0];
                }
                break;
            }
            case 16:
            {
                // Print the input integer, unsigned, in hexadecimal
                const value_type mask(base - 1);
                value_type val_copy(val);
                int i = size_bits;
                while( i >= 4 && ! value_traits_type::is_zero(val_copy) )
                {
                    // Print the next digit
                    *(--val_pos) = digits[large_int_cast<int>(
                        val_copy & mask)];
                    val_copy >>= 4;
                    i -= 4;
                }
                if( i != 0 && ! value_traits_type::is_zero(val_copy) )
                {
                    // Print the final digit
                    *(--val_pos) = digits[large_int_cast<int>(
                        val_copy & (mask >> (4 - i)))];
                }

                // Prepend a hexadecimal prefix, if requested
                if( flags & std::ios_base::showbase )
                {
                    *(--val_pos) = digits[base];
                    *(--val_pos) = digits[0];
                }
                break;
            }
            case 10:
            {
                // Print the input integer, signed, in decimal
                value_div_type div_result(val, value_type(0));
                const value_type large_base(base);
                do
                {
                    div_result = div(div_result.quot, large_base);
                    *(--val_pos) = digits[large_int_cast<int>(
                        abs(div_result.rem))];
                }
                while( ! value_traits_type::is_zero(div_result.quot) );

                // Prepend a sign, if applicable or requested
                const bool is_neg(value_traits_type::is_neg(val));
                if( is_neg || (flags & std::ios_base::showpos) )
                {
                    *(--val_pos) = "+-"[is_neg];
                }
                break;
            }
        }
    }

    // Write the string to the given output stream
    return( o << val_pos );
}

} // namespace large_int
} // namespace boost

#endif // BOOST_LARGE_INT_IO_HPP
