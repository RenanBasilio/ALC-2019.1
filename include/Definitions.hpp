#pragma once

// Use 80 bit double instead of 64 bit double. Adds 3 decimal places of precision.
#ifdef USE_EXTENDED_DOUBLE_PRECISION
    typedef long double real;
#elif USE_BOOST_RATIONAL
    #include <boost/multiprecision/cpp_int.hpp>
    typedef cpp_rational real;
#else
    typedef double real;
#endif