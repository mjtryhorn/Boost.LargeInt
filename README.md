Boost.LargeInt
==============

A platform-independent C++ library, for Boost, for the definition and transparent manipulation of integers of arbitrary size.

128bit or greater mathematics is commonly required where two or more large integer values must be combined together. For example, in the multiplication of two large, 64bit, signed or unsigned variables. How can we be certain that our calculation will not overflow? Either we restrict the range of our input - by returning an error, throwing an exception or worse - or we assume that overflow will never occur.

With Boost.LargeInt and its integral promotion, we can be sure that overflow will never occur.
For in-depth documentation and examples, please see [libs/large_int/doc/large_int.pdf](libs/large_int/doc/large_int.pdf).

Changes in v1.1.1:
* Fixes #2 - Static assertion failure in base.hpp, line 61
* Fixes #1 - Interpretation of hex string without prefix fails even when base is known (thanks to tomalakgeretkal!)
