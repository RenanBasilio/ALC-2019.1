#include <Differentials.hpp>
#include <Generators.hpp>

real computeDifferentialEuler( FirstOrderDifferential f, real x0, real y0, real x, real step ) {
    real y = y0;

    while ( x - x0 > std::numeric_limits<double>::epsilon() ) {
        y += f(x0, y) * step;
        x0 += step;
    }

    return y;
}

real computeDifferentialRengeKutta_SecondOrder ( FirstOrderDifferential f, real x0, real y0, real x, real step ) {
    real y = y0;

    while ( x - x0 > std::numeric_limits<double>::epsilon() ) {
        real k1 = f(x0, y);
        real k2 = f(x0 + step, y + step*k1);
        y += (k1 + k2) * step/2;
        x0 += step;
    }

    return y;
}

real computeDifferentialRengeKutta_FourthOrder ( FirstOrderDifferential f, real x0, real y0, real x, real step ) {
    real y = y0;

    while ( x - x0 > std::numeric_limits<double>::epsilon() ) {
        real k1 = f( x0, y );
        real k2 = f( x0 + step/2, y + step/2*k1 );
        real k3 = f( x0 + step/2, y + step/2*k2 );
        real k4 = f( x0 + step, y + step*k3 );
        y += step/6*( k1 + 2*k2 + 2*k3 + k4 );
        x0 += step;
    }

    return y;
}