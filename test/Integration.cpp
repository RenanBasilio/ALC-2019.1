#include <gtest/gtest.h>
#include <Integration.hpp>
#include <cmath>

constexpr double pi = 3.14159265358979323846;

TEST ( Integration, Polinomial ) {
    Function f = [](real x)->real{ return exp((-1)*pow(x, 2)); };

    EXPECT_NEAR( static_cast<double>( computeIntegral( f, 0, 1,  1, Polinomial)), 0.778801, 1e-6 );
    EXPECT_NEAR( static_cast<double>( computeIntegral( f, 0, 1,  2, Polinomial)),  0.68394, 1e-5 );
    EXPECT_NEAR( static_cast<double>( computeIntegral( f, 0, 1,  3, Polinomial)),  0.74718, 1e-5 );
    EXPECT_NEAR( static_cast<double>( computeIntegral( f, 0, 1,  4, Polinomial)),  0.74699, 1e-5 );
    EXPECT_NEAR( static_cast<double>( computeIntegral( f, 0, 1,  5, Polinomial)),  0.74683, 1e-5 );
    EXPECT_NEAR( static_cast<double>( computeIntegral( f, 0, 1, 10, Polinomial)),  0.74682, 1e-5 );
}

TEST ( Integration, Quadrature ) {
    Function f = [](real x)->real{ return (2 + x + 2*pow(x, 2)); };

    EXPECT_NEAR( static_cast<double>( computeIntegral( f, 1, 3, 2, Quadrature)), 25.333, 1e-3 );

    f = [](real x)->real{ return exp((-1)*pow(x, 2)); };
    EXPECT_NEAR( static_cast<double>( computeIntegral( f, 0, 1, 2, Quadrature)),  0.746, 1e-3 );

    f = [](real x)->real{ return (log(1-x)/x); };
    EXPECT_NEAR( static_cast<double>( computeIntegral( f, 0, 1, 10, Quadrature)), -pow(pi, 2)/6, 1e-2 );

    f = [](real x)->real{ return (log(1+x)/x); };
    EXPECT_NEAR( static_cast<double>( computeIntegral( f, 0, 1, 10, Quadrature)), pow(pi, 2)/12, 1e-2 );

    f = [](real x)->real{ return (log(1+pow(x, 2))/x); };
    EXPECT_NEAR( static_cast<double>( computeIntegral( f, 0, 1, 10, Quadrature)), pow(pi, 2)/24, 1e-2 );
}