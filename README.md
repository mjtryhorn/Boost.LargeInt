Boost.LargeInt
==============

A platform-independent C++ library, for Boost, for the definition and transparent manipulation of integers of arbitrary size.

For in-depth documentation, see [here](libs/large_int/doc/large_int.pdf).

Changes in v1.1.1:
* Fixes #1 - Static assertion failure in base.hpp, line 61
* Fixes #2 - Interpretation of hex string without prefix fails even when base is known (thanks to tomalakgeretkal!)
