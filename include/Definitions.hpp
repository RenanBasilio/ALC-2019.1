/**
 * This file contains preprocessor definitions and typedefs used throughout the project.
 */
#pragma once

#ifdef USE_EXTENDED_DOUBLE_PRECISION
    // Use 80 bit double instead of 64 bit double. Adds 3 decimal places of precision.
    typedef long double real;
#elif USE_BOOST_RATIONAL
    // Use Boost Rational instead of CPP double. Arbitrary precision.
    #include <boost/multiprecision/cpp_int.hpp>
    typedef cpp_rational real;
#else
    typedef double real;
#endif

// Defines a type named "Function" which is a pointer to a function which takes 
// and returns a real.
typedef real(*Function)(real);