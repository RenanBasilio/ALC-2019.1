#include <gtest/gtest.h>
#include <Differentials.hpp>
#include <cmath>

TEST ( Differentials, Euler ) {
    FirstOrderDifferential f = [](real t, real x)->real{ return t + x; };

    EXPECT_NEAR( static_cast<double>( computeDifferentialEuler( f, 0.0, 0.0, 0.1, 0.1 ) ), 0.00000, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialEuler( f, 0.0, 0.0, 0.2, 0.1 ) ), 0.01000, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialEuler( f, 0.0, 0.0, 0.3, 0.1 ) ), 0.03100, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialEuler( f, 0.0, 0.0, 0.4, 0.1 ) ), 0.06410, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialEuler( f, 0.0, 0.0, 0.5, 0.1 ) ), 0.11051, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialEuler( f, 0.0, 0.0, 0.6, 0.1 ) ), 0.17156, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialEuler( f, 0.0, 0.0, 0.7, 0.1 ) ), 0.24872, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialEuler( f, 0.0, 0.0, 0.8, 0.1 ) ), 0.34359, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialEuler( f, 0.0, 0.0, 0.9, 0.1 ) ), 0.45795, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialEuler( f, 0.0, 0.0, 1.0, 0.1 ) ), 0.59375, 1e-3 );
}

TEST ( Differentials, RengeKutta_SecondOrder ) {
    FirstOrderDifferential f = [](real t, real x)->real{ return t + x; };

    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_SecondOrder( f, 0.0, 0.0, 0.1, 0.1 ) ), 0.00500, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_SecondOrder( f, 0.0, 0.0, 0.2, 0.1 ) ), 0.02103, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_SecondOrder( f, 0.0, 0.0, 0.3, 0.1 ) ), 0.04923, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_SecondOrder( f, 0.0, 0.0, 0.4, 0.1 ) ), 0.09090, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_SecondOrder( f, 0.0, 0.0, 0.5, 0.1 ) ), 0.14744, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_SecondOrder( f, 0.0, 0.0, 0.6, 0.1 ) ), 0.22042, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_SecondOrder( f, 0.0, 0.0, 0.7, 0.1 ) ), 0.31156, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_SecondOrder( f, 0.0, 0.0, 0.8, 0.1 ) ), 0.42277, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_SecondOrder( f, 0.0, 0.0, 0.9, 0.1 ) ), 0.55616, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_SecondOrder( f, 0.0, 0.0, 1.0, 0.1 ) ), 0.71406, 1e-3 );
    
}

TEST ( Differentials, RengeKutta_FourthOrder ) {
    FirstOrderDifferential f = [](real t, real x)->real{ return t + x; };

    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_FourthOrder( f, 0.0, 0.0, 0.1, 0.1 ) ), 0.00517, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_FourthOrder( f, 0.0, 0.0, 0.2, 0.1 ) ), 0.02140, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_FourthOrder( f, 0.0, 0.0, 0.3, 0.1 ) ), 0.04986, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_FourthOrder( f, 0.0, 0.0, 0.4, 0.1 ) ), 0.09183, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_FourthOrder( f, 0.0, 0.0, 0.5, 0.1 ) ), 0.14873, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_FourthOrder( f, 0.0, 0.0, 0.6, 0.1 ) ), 0.22213, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_FourthOrder( f, 0.0, 0.0, 0.7, 0.1 ) ), 0.31376, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_FourthOrder( f, 0.0, 0.0, 0.8, 0.1 ) ), 0.42555, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_FourthOrder( f, 0.0, 0.0, 0.9, 0.1 ) ), 0.55961, 1e-3 );
    EXPECT_NEAR( static_cast<double>( computeDifferentialRengeKutta_FourthOrder( f, 0.0, 0.0, 1.0, 0.1 ) ), 0.71829, 1e-3 );
}