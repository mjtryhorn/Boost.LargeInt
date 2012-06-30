// large_int_test_base.cpp - Boost.LargeInt Library test file ----------------

// Copyright (c) 2012 Michael J. Tryhorn (mjtryhorn at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/ for latest version.
// ---------------------------------------------------------------------------

#include <boost/cstdint.hpp> // For int8_t, int16_t, int32_t, uint8_t, uint16_t
#include <boost/large_int.hpp>
#include <boost/large_int/io.hpp>

#define BOOST_TEST_MODULE boost_large_int_base
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( large_int_base )
{
    using boost::large_int::large_int;

    // Declare signed and unsigned 16 and 32bit integers for testing
    typedef large_int<uint8_t, int8_t> test_int16_t;
    typedef large_int<uint8_t, uint8_t> test_uint16_t;
    typedef large_int<test_uint16_t, test_int16_t> test_int32_t;
    typedef large_int<test_uint16_t, test_uint16_t> test_uint32_t;

    test_int16_t result_16;
    test_uint16_t result_u16;

    // Check construction and comparison against simple values
    BOOST_CHECK_EQUAL(test_int16_t(0), 0);
    BOOST_CHECK_EQUAL(test_int16_t(1), 1);
    BOOST_CHECK_EQUAL(test_int16_t(2), 2);
    BOOST_CHECK_EQUAL(test_int16_t(-1), -1);
    BOOST_CHECK_EQUAL(test_int16_t(-2), -2);
    BOOST_CHECK_EQUAL(test_uint16_t(0), 0);
    BOOST_CHECK_EQUAL(test_uint16_t(1), 1);
    BOOST_CHECK_EQUAL(test_uint16_t(2), 2);
    BOOST_CHECK_EQUAL(test_uint16_t(-1), uint16_t(-1));
    BOOST_CHECK_EQUAL(test_uint16_t(-2), uint16_t(-2));
    BOOST_CHECK_EQUAL(test_int16_t(0, 0x23), int32_t(0x23));
    BOOST_CHECK_EQUAL(test_int16_t(0xf123), int32_t(0xfffff123));
    BOOST_CHECK_EQUAL(test_int16_t(int8_t(0xf1), 0x23), int32_t(0xfffff123));
    BOOST_CHECK_EQUAL(test_uint16_t(0, 0x23), int32_t(0x23));
    BOOST_CHECK_EQUAL(test_uint16_t(0xf123), int32_t(0xf123));
    BOOST_CHECK_EQUAL(test_uint16_t(int8_t(0xf1), 0x23), int32_t(0xf123));
    BOOST_CHECK_EQUAL(test_int32_t(uint16_t(0xffff)), int32_t(0xffff));
    BOOST_CHECK_EQUAL(test_int32_t(int16_t(0xffff)), int32_t(0xffffffff));

    // Check copy construction
    BOOST_CHECK_EQUAL(test_int16_t(test_int16_t(0xf123)), int32_t(0xfffff123));
    BOOST_CHECK_EQUAL(test_int16_t(test_int32_t(0xf123)), int32_t(0xfffff123));
    BOOST_CHECK_EQUAL(test_int32_t(test_int16_t(0xf123)), int32_t(0xfffff123));
    BOOST_CHECK_EQUAL(test_int32_t(test_int32_t(0xf123)), int32_t(0xf123));

    // Check unary operator!
    BOOST_CHECK_EQUAL(!test_int16_t(0), true);
    BOOST_CHECK_EQUAL(!test_int16_t(1), false);
    BOOST_CHECK_EQUAL(!test_int16_t(-1), false);
    BOOST_CHECK_EQUAL(!test_uint16_t(0), true);
    BOOST_CHECK_EQUAL(!test_uint16_t(1), false);
    BOOST_CHECK_EQUAL(!test_uint16_t(-1), false);

    BOOST_CHECK_EQUAL(!test_int32_t(0), true);
    BOOST_CHECK_EQUAL(!test_int32_t(1), false);
    BOOST_CHECK_EQUAL(!test_int32_t(-1), false);
    BOOST_CHECK_EQUAL(!test_uint32_t(0), true);
    BOOST_CHECK_EQUAL(!test_uint32_t(1), false);
    BOOST_CHECK_EQUAL(!test_uint32_t(-1), false);

    // Check unary operator<bool_type>()
    if( test_int16_t(0) )
    {
        BOOST_ERROR("test_int16_t(0) == false failed");
    }
    if( test_int16_t(1) )
    {
        // Success
    }
    else
    {
        BOOST_ERROR("test_int16_t(1) == true failed");
    }
    if( test_int16_t(-1) )
    {
        // Success
    }
    else
    {
        BOOST_ERROR("test_int16_t(-1) == true failed");
    }

    // Check unary operator+
    BOOST_CHECK_EQUAL(+test_int16_t(0), 0);
    BOOST_CHECK_EQUAL(+test_int16_t(1), 1);
    BOOST_CHECK_EQUAL(+test_int16_t(2), 2);
    BOOST_CHECK_EQUAL(+test_int16_t(-1), -1);
    BOOST_CHECK_EQUAL(+test_uint16_t(0), 0);
    BOOST_CHECK_EQUAL(+test_uint16_t(1), 1);
    BOOST_CHECK_EQUAL(+test_uint16_t(2), 2);
    BOOST_CHECK_EQUAL(+test_uint16_t(-1), uint16_t(-1));

    // Check unary operator-
    BOOST_CHECK_EQUAL(-test_int16_t(0), 0);
    BOOST_CHECK_EQUAL(-test_int16_t(1), -1);
    BOOST_CHECK_EQUAL(-test_int16_t(2), -2);
    BOOST_CHECK_EQUAL(-test_int16_t(-1), 1);
    BOOST_CHECK_EQUAL(-test_uint16_t(0), 0);
    BOOST_CHECK_EQUAL(-test_uint16_t(1), uint16_t(-1));
    BOOST_CHECK_EQUAL(-test_uint16_t(2), uint16_t(-2));
    BOOST_CHECK_EQUAL(-test_uint16_t(-1), uint16_t(1));

    // Check unary operator~
    BOOST_CHECK_EQUAL(~test_int16_t(0), int16_t(0xffff));
    BOOST_CHECK_EQUAL(~test_int16_t(1), int16_t(0xfffe));
    BOOST_CHECK_EQUAL(~test_int16_t(2), int16_t(0xfffd));
    BOOST_CHECK_EQUAL(~test_int16_t(-1), 0);
    BOOST_CHECK_EQUAL(~test_uint16_t(0), uint16_t(0xffff));
    BOOST_CHECK_EQUAL(~test_uint16_t(1), uint16_t(0xfffe));
    BOOST_CHECK_EQUAL(~test_uint16_t(2), uint16_t(0xfffd));
    BOOST_CHECK_EQUAL(~test_uint16_t(-1), 0);

    // Check operator++
    BOOST_CHECK_EQUAL(++test_int16_t(0), 1);
    BOOST_CHECK_EQUAL(++test_int16_t(1), 2);
    BOOST_CHECK_EQUAL(++test_int16_t(2), 3);
    BOOST_CHECK_EQUAL(++test_int16_t(-1), 0);
    BOOST_CHECK_EQUAL(++test_int16_t(-2), -1);
    BOOST_CHECK_EQUAL(++test_int16_t(0xfe), 0xff);
    BOOST_CHECK_EQUAL(++test_int16_t(0xff), 0x100);
    BOOST_CHECK_EQUAL(++test_int16_t(0x7fff), int16_t(0x8000));
    BOOST_CHECK_EQUAL(++(++test_int16_t(-1)), 1);

    BOOST_CHECK_EQUAL(++test_uint16_t(0), 1);
    BOOST_CHECK_EQUAL(++test_uint16_t(1), 2);
    BOOST_CHECK_EQUAL(++test_uint16_t(2), 3);
    BOOST_CHECK_EQUAL(++test_uint16_t(-1), 0);
    BOOST_CHECK_EQUAL(++test_uint16_t(-2), uint16_t(0xffff));
    BOOST_CHECK_EQUAL(++test_uint16_t(0xfe), 0xff);
    BOOST_CHECK_EQUAL(++test_uint16_t(0xff), 0x100);
    BOOST_CHECK_EQUAL(++test_uint16_t(0x7fff), uint16_t(0x8000));
    BOOST_CHECK_EQUAL(++(++test_uint16_t(-1)), 1);

    result_16 = test_int16_t(-2);
    BOOST_CHECK_EQUAL(result_16++, -2);
    BOOST_CHECK_EQUAL(result_16++, -1);
    BOOST_CHECK_EQUAL(result_16++, 0);
    BOOST_CHECK_EQUAL(result_16++, 1);
    BOOST_CHECK_EQUAL(result_16++, 2);

    result_u16 = test_uint16_t(-2);
    BOOST_CHECK_EQUAL(result_u16++, uint16_t(-2));
    BOOST_CHECK_EQUAL(result_u16++, uint16_t(-1));
    BOOST_CHECK_EQUAL(result_u16++, 0);
    BOOST_CHECK_EQUAL(result_u16++, 1);
    BOOST_CHECK_EQUAL(result_u16++, 2);

    // Check operator--
    BOOST_CHECK_EQUAL(--test_int16_t(0), -1);
    BOOST_CHECK_EQUAL(--test_int16_t(1), 0);
    BOOST_CHECK_EQUAL(--test_int16_t(2), 1);
    BOOST_CHECK_EQUAL(--test_int16_t(-1), -2);
    BOOST_CHECK_EQUAL(--test_int16_t(-2), -3);
    BOOST_CHECK_EQUAL(--test_int16_t(0xff), 0xfe);
    BOOST_CHECK_EQUAL(--test_int16_t(0x100), 0xff);
    BOOST_CHECK_EQUAL(--test_int16_t(0x8000), int16_t(0x7fff));
    BOOST_CHECK_EQUAL(--(--test_int16_t(-1)), -3);

    BOOST_CHECK_EQUAL(--test_uint16_t(0), uint16_t(-1));
    BOOST_CHECK_EQUAL(--test_uint16_t(1), 0);
    BOOST_CHECK_EQUAL(--test_uint16_t(2), 1);
    BOOST_CHECK_EQUAL(--test_uint16_t(-1), uint16_t(-2));
    BOOST_CHECK_EQUAL(--test_uint16_t(-2), uint16_t(-3));
    BOOST_CHECK_EQUAL(--test_uint16_t(0xff), 0xfe);
    BOOST_CHECK_EQUAL(--test_uint16_t(0x100), 0xff);
    BOOST_CHECK_EQUAL(--test_uint16_t(0x8000), uint16_t(0x7fff));
    BOOST_CHECK_EQUAL(--(--test_uint16_t(-1)), uint16_t(-3));

    result_16 = test_int16_t(2);
    BOOST_CHECK_EQUAL(result_16--, 2);
    BOOST_CHECK_EQUAL(result_16--, 1);
    BOOST_CHECK_EQUAL(result_16--, 0);
    BOOST_CHECK_EQUAL(result_16--, -1);
    BOOST_CHECK_EQUAL(result_16--, -2);

    result_u16 = test_uint16_t(2);
    BOOST_CHECK_EQUAL(result_u16--, 2);
    BOOST_CHECK_EQUAL(result_u16--, 1);
    BOOST_CHECK_EQUAL(result_u16--, 0);
    BOOST_CHECK_EQUAL(result_u16--, uint16_t(-1));
    BOOST_CHECK_EQUAL(result_u16--, uint16_t(-2));

    // Check operator+=
    result_16 = test_int16_t(-1);
    BOOST_CHECK_EQUAL(result_16 += 1, 0);
    BOOST_CHECK_EQUAL(result_16 += -1, -1);
    BOOST_CHECK_EQUAL(result_16 += 2, 1);
    BOOST_CHECK_EQUAL(result_16 += 3, 4);
    BOOST_CHECK_EQUAL(result_16 += 0xfc, 0x100);

    result_u16 = test_uint16_t(-1);
    BOOST_CHECK_EQUAL(result_u16 += 1, 0);
    BOOST_CHECK_EQUAL(result_u16 += -1, uint16_t(-1));
    BOOST_CHECK_EQUAL(result_u16 += 2, 1);
    BOOST_CHECK_EQUAL(result_u16 += 3, 4);
    BOOST_CHECK_EQUAL(result_u16 += 0xfc, 0x100);

    // Check operator-=
    result_16 = test_int16_t(1);
    BOOST_CHECK_EQUAL(result_16 -= 1, 0);
    BOOST_CHECK_EQUAL(result_16 -= -1, 1);
    BOOST_CHECK_EQUAL(result_16 -= 2, -1);
    BOOST_CHECK_EQUAL(result_16 -= 3, -4);
    BOOST_CHECK_EQUAL(result_16 -= 0xfd, int16_t(~0x100));

    result_u16 = test_uint16_t(1);
    BOOST_CHECK_EQUAL(result_u16 -= 1, 0);
    BOOST_CHECK_EQUAL(result_u16 -= -1, 1);
    BOOST_CHECK_EQUAL(result_u16 -= 2, uint16_t(-1));
    BOOST_CHECK_EQUAL(result_u16 -= 3, uint16_t(-4));
    BOOST_CHECK_EQUAL(result_u16 -= 0xfd, uint16_t(~0x100));

    // Check operator*=
    result_16 = test_int16_t(1);
    BOOST_CHECK_EQUAL(result_16 *= 1, 1);
    BOOST_CHECK_EQUAL(result_16 *= -1, -1);
    BOOST_CHECK_EQUAL(result_16 *= 2, -2);
    BOOST_CHECK_EQUAL(result_16 *= 3, -6);
    BOOST_CHECK_EQUAL(result_16 *= -4, 24);

    result_u16 = test_uint16_t(1);
    BOOST_CHECK_EQUAL(result_u16 *= 1, 1);
    BOOST_CHECK_EQUAL(result_u16 *= -1, uint16_t(-1));
    BOOST_CHECK_EQUAL(result_u16 *= 2, uint16_t(-2));
    BOOST_CHECK_EQUAL(result_u16 *= 3, uint16_t(-6));
    BOOST_CHECK_EQUAL(result_u16 *= -4, 24);

    // Check operator/=
    // (Note that as this operator is implemented via a single call
    // to boost::large_int::div only superficial testing is required here.)
    result_16 = test_int16_t(9);
    BOOST_CHECK_EQUAL(result_16 /= 1, 9);
    BOOST_CHECK_EQUAL(result_16 /= -1, -9);
    BOOST_CHECK_EQUAL(result_16 /= 3, -3);
    BOOST_CHECK_EQUAL(result_16 /= 2, -1);

    result_u16 = test_uint16_t(9);
    BOOST_CHECK_EQUAL(result_u16 /= 1, 9);
    BOOST_CHECK_EQUAL(result_u16 /= 2, 4);
    BOOST_CHECK_EQUAL(result_u16 /= -1, 0); // [-1 becomes +65535 when promoted to unsigned 16bit]

    // Check operator%=
    // (Note that as this operator is implemented via a single call
    // to boost::large_int::div only superficial testing is required here.)
    result_16 = test_int16_t(3);
    BOOST_CHECK_EQUAL((result_16 = 3, result_16 %= 1), 0);
    BOOST_CHECK_EQUAL((result_16 = 3, result_16 %= -1), 0);
    BOOST_CHECK_EQUAL((result_16 = 3, result_16 %= 2), 1);
    BOOST_CHECK_EQUAL((result_16 = 3, result_16 %= -2), 1);
    BOOST_CHECK_EQUAL((result_16 = 3, result_16 %= 3), 0);
    BOOST_CHECK_EQUAL((result_16 = 3, result_16 %= 4), 3);

    result_u16 = test_uint16_t(3);
    BOOST_CHECK_EQUAL((result_u16 = 3, result_u16 %= 1), 0);
    BOOST_CHECK_EQUAL((result_u16 = 3, result_u16 %= -1), 3); // [-1 becomes +65535 when promoted to unsigned 16bit]
    BOOST_CHECK_EQUAL((result_u16 = 3, result_u16 %= 2), 1);
    BOOST_CHECK_EQUAL((result_u16 = 3, result_u16 %= -2), 3); // [-2 becomes +65534 when promoted to unsigned 16bit]
    BOOST_CHECK_EQUAL((result_u16 = 3, result_u16 %= 3), 0);
    BOOST_CHECK_EQUAL((result_u16 = 3, result_u16 %= 4), 3);

    // Check operator|=
    result_16 = test_int16_t(0);
    BOOST_CHECK_EQUAL(result_16 |= 1, 1);
    BOOST_CHECK_EQUAL(result_16 |= 2, 3);
    BOOST_CHECK_EQUAL(result_16 |= 3, 3);
    BOOST_CHECK_EQUAL(result_16 |= 0xf00, 0xf03);
    BOOST_CHECK_EQUAL(result_16 |= -1, -1);

    result_u16 = test_uint16_t(0);
    BOOST_CHECK_EQUAL(result_u16 |= 1, 1);
    BOOST_CHECK_EQUAL(result_u16 |= 2, 3);
    BOOST_CHECK_EQUAL(result_u16 |= 3, 3);
    BOOST_CHECK_EQUAL(result_u16 |= 0xf00, 0xf03);
    BOOST_CHECK_EQUAL(result_u16 |= -1, uint16_t(-1));

    // Check operator&=
    result_16 = test_int16_t(-1);
    BOOST_CHECK_EQUAL(result_16 &= -1, -1);
    BOOST_CHECK_EQUAL(result_16 &= 0xf07, 0xf07);
    BOOST_CHECK_EQUAL(result_16 &= 3, 3);
    BOOST_CHECK_EQUAL(result_16 &= 2, 2);
    BOOST_CHECK_EQUAL(result_16 &= 1, 0);

    result_u16 = test_uint16_t(-1);
    BOOST_CHECK_EQUAL(result_u16 &= -1, uint16_t(-1));
    BOOST_CHECK_EQUAL(result_u16 &= 0xf07, 0xf07);
    BOOST_CHECK_EQUAL(result_u16 &= 3, 3);
    BOOST_CHECK_EQUAL(result_u16 &= 2, 2);
    BOOST_CHECK_EQUAL(result_u16 &= 1, 0);

    // Check operator^=
    result_16 = test_int16_t(-1);
    BOOST_CHECK_EQUAL(result_16 ^= 3, ~3);
    BOOST_CHECK_EQUAL(result_16 ^= 2, ~1);
    BOOST_CHECK_EQUAL(result_16 ^= 1, ~0);
    BOOST_CHECK_EQUAL(result_16 ^= 0xf07, int16_t(0xf0f8));
    BOOST_CHECK_EQUAL(result_16 ^= -1, 0xf07);

    result_u16 = test_uint16_t(-1);
    BOOST_CHECK_EQUAL(result_u16 ^= 3, uint16_t(~3));
    BOOST_CHECK_EQUAL(result_u16 ^= 2, uint16_t(~1));
    BOOST_CHECK_EQUAL(result_u16 ^= 1, uint16_t(~0));
    BOOST_CHECK_EQUAL(result_u16 ^= 0xf07, uint16_t(0xf0f8));
    BOOST_CHECK_EQUAL(result_u16 ^= -1, 0xf07);

    // Check operator<<=
    result_16 = test_int16_t(1);
    BOOST_CHECK_EQUAL(result_16 <<= 0, 1);
    BOOST_CHECK_EQUAL(result_16 <<= 1, 2);
    BOOST_CHECK_EQUAL(result_16 <<= 1, 4);
    BOOST_CHECK_EQUAL(result_16 <<= 2, 16);
    BOOST_CHECK_EQUAL(result_16 <<= 8, 4096);
    BOOST_CHECK_EQUAL(result_16 <<= 16, 4096); // Due to: bits %= size
    BOOST_CHECK_EQUAL(result_16 <<= 17, 8192); // Due to: bits %= size

    result_u16 = test_uint16_t(1);
    BOOST_CHECK_EQUAL(result_u16 <<= 0, 1);
    BOOST_CHECK_EQUAL(result_u16 <<= 1, 2);
    BOOST_CHECK_EQUAL(result_u16 <<= 1, 4);
    BOOST_CHECK_EQUAL(result_u16 <<= 2, 16);
    BOOST_CHECK_EQUAL(result_u16 <<= 8, 4096);
    BOOST_CHECK_EQUAL(result_u16 <<= 16, 4096); // Due to: bits %= size
    BOOST_CHECK_EQUAL(result_u16 <<= 17, 8192); // Due to: bits %= size

    // Check operator>>=
    result_16 = test_int16_t(8192);
    BOOST_CHECK_EQUAL(result_16 >>= 0, 8192);
    BOOST_CHECK_EQUAL(result_16 >>= 1, 4096);
    BOOST_CHECK_EQUAL(result_16 >>= 1, 2048);
    BOOST_CHECK_EQUAL(result_16 >>= 2, 512);
    BOOST_CHECK_EQUAL(result_16 >>= 8, 2);
    BOOST_CHECK_EQUAL(result_16 >>= 16, 2); // Due to: bits %= size
    BOOST_CHECK_EQUAL(result_16 >>= 17, 1); // Due to: bits %= size

    result_u16 = test_uint16_t(8192);
    BOOST_CHECK_EQUAL(result_u16 >>= 0, 8192);
    BOOST_CHECK_EQUAL(result_u16 >>= 1, 4096);
    BOOST_CHECK_EQUAL(result_u16 >>= 1, 2048);
    BOOST_CHECK_EQUAL(result_u16 >>= 2, 512);
    BOOST_CHECK_EQUAL(result_u16 >>= 8, 2);
    BOOST_CHECK_EQUAL(result_u16 >>= 16, 2); // Due to: bits %= size
    BOOST_CHECK_EQUAL(result_u16 >>= 17, 1); // Due to: bits %= size

    // Check that operator>> preserves the sign bit for signed values only
    result_16 = test_int16_t(0x8000);
    result_u16 = test_uint16_t(0x8000);
    BOOST_CHECK_EQUAL(result_16 >>= 0, int16_t(0x8000));
    BOOST_CHECK_EQUAL(result_16 >>= 1, int16_t(0xc000));
    BOOST_CHECK_EQUAL(result_16 >>= 1, int16_t(0xe000));
    BOOST_CHECK_EQUAL(result_16 >>= 1, int16_t(0xf000));
    BOOST_CHECK_EQUAL(result_16 >>= 2, int16_t(0xfc00));
    BOOST_CHECK_EQUAL(result_u16 >>= 0, uint16_t(0x8000));
    BOOST_CHECK_EQUAL(result_u16 >>= 1, uint16_t(0x4000));
    BOOST_CHECK_EQUAL(result_u16 >>= 1, uint16_t(0x2000));
    BOOST_CHECK_EQUAL(result_u16 >>= 1, uint16_t(0x1000));
    BOOST_CHECK_EQUAL(result_u16 >>= 2, uint16_t(0x0400));
}

BOOST_AUTO_TEST_CASE( large_int_compare )
{
    using boost::large_int::large_int;

    // Declare signed and unsigned 16 and 32bit integers for testing
    typedef large_int<uint8_t, int8_t> test_int16_t;
    typedef large_int<uint8_t, uint8_t> test_uint16_t;
    typedef large_int<test_uint16_t, test_int16_t> test_int32_t;
    typedef large_int<test_uint16_t, test_uint16_t> test_uint32_t;

    // All large_int comparison operators are implemented in terms of:
    // boost::large_int::large_int_traits<...>::lt,
    // boost::large_int::large_int_traits<...>::lt_literal,
    // boost::large_int::large_int_traits<...>::eq,
    // boost::large_int::large_int_traits<...>::eq_literal,
    // Because of this, only superficial testing is required here.

    // Compare integer types against themselves
    BOOST_CHECK_EQUAL(test_int16_t(1), test_int16_t(1));
    BOOST_CHECK_EQUAL(test_uint16_t(2), test_uint16_t(2));
    BOOST_CHECK_EQUAL(test_int32_t(3), test_int32_t(3));
    BOOST_CHECK_EQUAL(test_uint32_t(4), test_uint32_t(4));

    // Compare 16bit and 32bit integer types against each other
    BOOST_CHECK_EQUAL(test_int16_t(1), test_int32_t(1));
    BOOST_CHECK_EQUAL(test_int16_t(-1), test_int32_t(-1));
    BOOST_CHECK_EQUAL(test_uint16_t(1), test_uint32_t(1));
    BOOST_CHECK_EQUAL(test_uint16_t(-1), test_uint32_t(uint16_t(-1)));
    BOOST_CHECK_EQUAL(test_int16_t(1), test_uint32_t(1));
    BOOST_CHECK_EQUAL(test_int16_t(-1), test_uint32_t(-1));
    BOOST_CHECK_EQUAL(test_uint16_t(1), test_int32_t(1));
    BOOST_CHECK_EQUAL(test_uint16_t(-1), test_int32_t(uint16_t(-1)));

    // Check operator <
    BOOST_CHECK_EQUAL(test_int16_t(0) < test_int16_t(0), false);
    BOOST_CHECK_EQUAL(test_int16_t(0) < test_int16_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) < test_int16_t(0), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) < test_int16_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(0) < test_int32_t(0), false);
    BOOST_CHECK_EQUAL(test_int16_t(0) < test_int32_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) < test_int32_t(0), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) < test_int32_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) < test_int32_t(2), true);
    BOOST_CHECK_EQUAL(test_int16_t(2) < test_int32_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(2) < test_int32_t(2), false);

    // Check operator <=
    BOOST_CHECK_EQUAL(test_int16_t(0) <= test_int16_t(0), true);
    BOOST_CHECK_EQUAL(test_int16_t(0) <= test_int16_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) <= test_int16_t(0), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) <= test_int16_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(0) <= test_int32_t(0), true);
    BOOST_CHECK_EQUAL(test_int16_t(0) <= test_int32_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) <= test_int32_t(0), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) <= test_int32_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) <= test_int32_t(2), true);
    BOOST_CHECK_EQUAL(test_int16_t(2) <= test_int32_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(2) <= test_int32_t(2), true);

    // Check operator ==
    BOOST_CHECK_EQUAL(test_int16_t(0) == test_int16_t(0), true);
    BOOST_CHECK_EQUAL(test_int16_t(0) == test_int16_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) == test_int16_t(0), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) == test_int16_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(0) == test_int32_t(0), true);
    BOOST_CHECK_EQUAL(test_int16_t(0) == test_int32_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) == test_int32_t(0), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) == test_int32_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) == test_int32_t(2), false);
    BOOST_CHECK_EQUAL(test_int16_t(2) == test_int32_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(2) == test_int32_t(2), true);

    // Check operator !=
    BOOST_CHECK_EQUAL(test_int16_t(0) != test_int16_t(0), false);
    BOOST_CHECK_EQUAL(test_int16_t(0) != test_int16_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) != test_int16_t(0), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) != test_int16_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(0) != test_int32_t(0), false);
    BOOST_CHECK_EQUAL(test_int16_t(0) != test_int32_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) != test_int32_t(0), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) != test_int32_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) != test_int32_t(2), true);
    BOOST_CHECK_EQUAL(test_int16_t(2) != test_int32_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(2) != test_int32_t(2), false);

    // Check operator >=
    BOOST_CHECK_EQUAL(test_int16_t(0) >= test_int16_t(0), true);
    BOOST_CHECK_EQUAL(test_int16_t(0) >= test_int16_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) >= test_int16_t(0), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) >= test_int16_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(0) >= test_int32_t(0), true);
    BOOST_CHECK_EQUAL(test_int16_t(0) >= test_int32_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) >= test_int32_t(0), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) >= test_int32_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) >= test_int32_t(2), false);
    BOOST_CHECK_EQUAL(test_int16_t(2) >= test_int32_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(2) >= test_int32_t(2), true);

    // Check operator >
    BOOST_CHECK_EQUAL(test_int16_t(0) > test_int16_t(0), false);
    BOOST_CHECK_EQUAL(test_int16_t(0) > test_int16_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) > test_int16_t(0), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) > test_int16_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(0) > test_int32_t(0), false);
    BOOST_CHECK_EQUAL(test_int16_t(0) > test_int32_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) > test_int32_t(0), true);
    BOOST_CHECK_EQUAL(test_int16_t(1) > test_int32_t(1), false);
    BOOST_CHECK_EQUAL(test_int16_t(1) > test_int32_t(2), false);
    BOOST_CHECK_EQUAL(test_int16_t(2) > test_int32_t(1), true);
    BOOST_CHECK_EQUAL(test_int16_t(2) > test_int32_t(2), false);

    // Check operator < (for literal values)
    BOOST_CHECK_EQUAL(test_int16_t(0) < 0, false);
    BOOST_CHECK_EQUAL(test_int16_t(0) < 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) < 0, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) < 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(0) < 0, false);
    BOOST_CHECK_EQUAL(test_int16_t(0) < 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) < 0, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) < 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) < 2, true);
    BOOST_CHECK_EQUAL(test_int16_t(2) < 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(2) < 2, false);

    BOOST_CHECK_EQUAL(0 < test_int16_t(0), false);
    BOOST_CHECK_EQUAL(0 < test_int16_t(1), true);
    BOOST_CHECK_EQUAL(1 < test_int16_t(0), false);
    BOOST_CHECK_EQUAL(1 < test_int16_t(1), false);
    BOOST_CHECK_EQUAL(0 < test_int16_t(0), false);
    BOOST_CHECK_EQUAL(0 < test_int16_t(1), true);
    BOOST_CHECK_EQUAL(1 < test_int16_t(0), false);
    BOOST_CHECK_EQUAL(1 < test_int16_t(1), false);
    BOOST_CHECK_EQUAL(1 < test_int16_t(2), true);
    BOOST_CHECK_EQUAL(2 < test_int16_t(1), false);
    BOOST_CHECK_EQUAL(2 < test_int16_t(2), false);

    // Check operator <= (for literal values)
    BOOST_CHECK_EQUAL(test_int16_t(0) <= 0, true);
    BOOST_CHECK_EQUAL(test_int16_t(0) <= 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) <= 0, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) <= 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(0) <= 0, true);
    BOOST_CHECK_EQUAL(test_int16_t(0) <= 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) <= 0, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) <= 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) <= 2, true);
    BOOST_CHECK_EQUAL(test_int16_t(2) <= 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(2) <= 2, true);

    BOOST_CHECK_EQUAL(0 <= test_int16_t(0), true);
    BOOST_CHECK_EQUAL(0 <= test_int16_t(1), true);
    BOOST_CHECK_EQUAL(1 <= test_int16_t(0), false);
    BOOST_CHECK_EQUAL(1 <= test_int16_t(1), true);
    BOOST_CHECK_EQUAL(0 <= test_int16_t(0), true);
    BOOST_CHECK_EQUAL(0 <= test_int16_t(1), true);
    BOOST_CHECK_EQUAL(1 <= test_int16_t(0), false);
    BOOST_CHECK_EQUAL(1 <= test_int16_t(1), true);
    BOOST_CHECK_EQUAL(1 <= test_int16_t(2), true);
    BOOST_CHECK_EQUAL(2 <= test_int16_t(1), false);
    BOOST_CHECK_EQUAL(2 <= test_int16_t(2), true);

    // Check operator == (for literal values)
    BOOST_CHECK_EQUAL(test_int16_t(0) == 0, true);
    BOOST_CHECK_EQUAL(test_int16_t(0) == 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) == 0, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) == 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(0) == 0, true);
    BOOST_CHECK_EQUAL(test_int16_t(0) == 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) == 0, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) == 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) == 2, false);
    BOOST_CHECK_EQUAL(test_int16_t(2) == 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(2) == 2, true);

    BOOST_CHECK_EQUAL(0 == test_int16_t(0), true);
    BOOST_CHECK_EQUAL(0 == test_int16_t(1), false);
    BOOST_CHECK_EQUAL(1 == test_int16_t(0), false);
    BOOST_CHECK_EQUAL(1 == test_int16_t(1), true);
    BOOST_CHECK_EQUAL(0 == test_int16_t(0), true);
    BOOST_CHECK_EQUAL(0 == test_int16_t(1), false);
    BOOST_CHECK_EQUAL(1 == test_int16_t(0), false);
    BOOST_CHECK_EQUAL(1 == test_int16_t(1), true);
    BOOST_CHECK_EQUAL(1 == test_int16_t(2), false);
    BOOST_CHECK_EQUAL(2 == test_int16_t(1), false);
    BOOST_CHECK_EQUAL(2 == test_int16_t(2), true);

    // Check operator != (for literal values)
    BOOST_CHECK_EQUAL(test_int16_t(0) != 0, false);
    BOOST_CHECK_EQUAL(test_int16_t(0) != 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) != 0, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) != 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(0) != 0, false);
    BOOST_CHECK_EQUAL(test_int16_t(0) != 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) != 0, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) != 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) != 2, true);
    BOOST_CHECK_EQUAL(test_int16_t(2) != 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(2) != 2, false);

    BOOST_CHECK_EQUAL(0 != test_int16_t(0), false);
    BOOST_CHECK_EQUAL(0 != test_int16_t(1), true);
    BOOST_CHECK_EQUAL(1 != test_int16_t(0), true);
    BOOST_CHECK_EQUAL(1 != test_int16_t(1), false);
    BOOST_CHECK_EQUAL(0 != test_int16_t(0), false);
    BOOST_CHECK_EQUAL(0 != test_int16_t(1), true);
    BOOST_CHECK_EQUAL(1 != test_int16_t(0), true);
    BOOST_CHECK_EQUAL(1 != test_int16_t(1), false);
    BOOST_CHECK_EQUAL(1 != test_int16_t(2), true);
    BOOST_CHECK_EQUAL(2 != test_int16_t(1), true);
    BOOST_CHECK_EQUAL(2 != test_int16_t(2), false);

    // Check operator >= (for literal values)
    BOOST_CHECK_EQUAL(test_int16_t(0) >= 0, true);
    BOOST_CHECK_EQUAL(test_int16_t(0) >= 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) >= 0, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) >= 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(0) >= 0, true);
    BOOST_CHECK_EQUAL(test_int16_t(0) >= 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) >= 0, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) >= 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) >= 2, false);
    BOOST_CHECK_EQUAL(test_int16_t(2) >= 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(2) >= 2, true);

    BOOST_CHECK_EQUAL(0 >= test_int16_t(0), true);
    BOOST_CHECK_EQUAL(0 >= test_int16_t(1), false);
    BOOST_CHECK_EQUAL(1 >= test_int16_t(0), true);
    BOOST_CHECK_EQUAL(1 >= test_int16_t(1), true);
    BOOST_CHECK_EQUAL(0 >= test_int16_t(0), true);
    BOOST_CHECK_EQUAL(0 >= test_int16_t(1), false);
    BOOST_CHECK_EQUAL(1 >= test_int16_t(0), true);
    BOOST_CHECK_EQUAL(1 >= test_int16_t(1), true);
    BOOST_CHECK_EQUAL(1 >= test_int16_t(2), false);
    BOOST_CHECK_EQUAL(2 >= test_int16_t(1), true);
    BOOST_CHECK_EQUAL(2 >= test_int16_t(2), true);

    // Check operator > (for literal values)
    BOOST_CHECK_EQUAL(test_int16_t(0) > 0, false);
    BOOST_CHECK_EQUAL(test_int16_t(0) > 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) > 0, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) > 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(0) > 0, false);
    BOOST_CHECK_EQUAL(test_int16_t(0) > 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) > 0, true);
    BOOST_CHECK_EQUAL(test_int16_t(1) > 1, false);
    BOOST_CHECK_EQUAL(test_int16_t(1) > 2, false);
    BOOST_CHECK_EQUAL(test_int16_t(2) > 1, true);
    BOOST_CHECK_EQUAL(test_int16_t(2) > 2, false);

    BOOST_CHECK_EQUAL(0 > test_int16_t(0), false);
    BOOST_CHECK_EQUAL(0 > test_int16_t(1), false);
    BOOST_CHECK_EQUAL(1 > test_int16_t(0), true);
    BOOST_CHECK_EQUAL(1 > test_int16_t(1), false);
    BOOST_CHECK_EQUAL(0 > test_int16_t(0), false);
    BOOST_CHECK_EQUAL(0 > test_int16_t(1), false);
    BOOST_CHECK_EQUAL(1 > test_int16_t(0), true);
    BOOST_CHECK_EQUAL(1 > test_int16_t(1), false);
    BOOST_CHECK_EQUAL(1 > test_int16_t(2), false);
    BOOST_CHECK_EQUAL(2 > test_int16_t(1), true);
    BOOST_CHECK_EQUAL(2 > test_int16_t(2), false);
}
