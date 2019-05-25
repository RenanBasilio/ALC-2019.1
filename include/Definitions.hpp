/**
 * This file contains preprocessor definitions and typedefs used throughout the project.
 */
#pragma once

#ifdef USE_EXTENDED_DOUBLE_PRECISION
    // Use 80 bit double instead of 64 bit double. Adds 3 decimal places of precision.
    typedef long double real;
#elif USE_BOOST_RATIONAL
    // Use Boost multiprecision float instead of CPP double. Precision of up to 100 decimal places.
    #include <boost/multiprecision/cpp_dec_float.hpp>
    typedef boost::multiprecision::cpp_dec_float_100 real;
#else
    typedef double real;
#endif

// Defines a type named "Function" which is a pointer to a function which takes 
// and returns a real.
typedef real(*Function)(real);