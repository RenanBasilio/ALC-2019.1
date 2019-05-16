#include <gtest/gtest.h>
#include <Integration.hpp>
#include <cmath>

TEST ( Integration, Polinomial ) {
    Function f = [](double x)->double{ return std::exp((-1)*std::pow(x, 2)); };

    EXPECT_NEAR( computeIntegral( f, 0, 1,  1, Polinomial ), 0.778801, 1e-6 );
    EXPECT_NEAR( computeIntegral( f, 0, 1,  2, Polinomial ), 0.68394,  1e-5 );
    EXPECT_NEAR( computeIntegral( f, 0, 1,  3, Polinomial ), 0.74718,  1e-5 );
    EXPECT_NEAR( computeIntegral( f, 0, 1,  4, Polinomial ), 0.74699,  1e-5 );
    EXPECT_NEAR( computeIntegral( f, 0, 1,  5, Polinomial ), 0.74683,  1e-5 );
    EXPECT_NEAR( computeIntegral( f, 0, 1, 10, Polinomial ), 0.74682,  1e-5 );
}