#include <Differentials.hpp>
#include <Generators.hpp>
#include <iostream>

real computeDifferentialEuler( FirstOrderDifferential f, real x0, real y0, real x, real step, bool verbose ) {
    real y = y0;

    while ( x - x0 > std::numeric_limits<double>::epsilon() ) {
        if (verbose) std::cout << x0 << "," << y << std::endl;
        y += f(x0, y) * step;
        x0 += step;
    }
    if (verbose) std::cout << x0 << "," << y << std::endl;

    return y;
}

real computeDifferentialRungeKutta_SecondOrder ( FirstOrderDifferential f, real x0, real y0, real x, real step, bool verbose ) {
    real y = y0;

    while ( x - x0 > std::numeric_limits<double>::epsilon() ) {
        if (verbose) std::cout << x0 << "," << y << std::endl;
        real k1 = f(x0, y);
        real k2 = f(x0 + step, y + step*k1);
        y += (k1 + k2) * step/2;
        x0 += step;
    }
    if (verbose) std::cout << x0 << "," << y << std::endl;

    return y;
}

real computeDifferentialRungeKutta_FourthOrder ( FirstOrderDifferential f, real x0, real y0, real x, real step, bool verbose ) {
    real y = y0;

    while ( x - x0 > std::numeric_limits<double>::epsilon() ) {
        if (verbose) std::cout << x0 << "," << y << std::endl;
        real k1 = f( x0, y );
        real k2 = f( x0 + step/2, y + step/2*k1 );
        real k3 = f( x0 + step/2, y + step/2*k2 );
        real k4 = f( x0 + step, y + step*k3 );
        y += step/6*( k1 + 2*k2 + 2*k3 + k4 );
        x0 += step;
    }
    if (verbose) std::cout << x0 << "," << y << std::endl;

    return y;
}

real computeDifferentialTaylor( SecondOrderDifferential f, real x0, real y0, real yy0, real x, real step, bool verbose ) {
    real y = y0;
    real yy = yy0;
    real yyy;

    while ( x - x0 > std::numeric_limits<double>::epsilon() ) {
        if (verbose) std::cout << x0 << "," << y << std::endl;
        yyy = f( x0, y, yy );
        y += yy * step + yyy * step * step / 2;
        yy += yyy * step;
        x0 += step;
    }
    if (verbose) std::cout << x0 << "," << y << std::endl;

    return y;
}

real computeDifferentialRungeKuttaNystrom( SecondOrderDifferential f, real x0, real y0, real yy0, real x, real step, bool verbose ) {
    real y = y0;
    real yy = yy0;

    while ( x - x0 > std::numeric_limits<double>::epsilon() ) {
        if (verbose) std::cout << x0 << "," << y << "," << yy << std::endl;
        real q, l, k1, k2, k3, k4;

        real v = f( x0, y, yy );

        k1 = 0.5 * step * f( x0, y, yy );
        q  = 0.5 * step * ( yy + 0.5 * k1 );
        k2 = 0.5 * step * f( x0 + step/2.0, y + q, yy + k1 );
        k3 = 0.5 * step * f( x0 + step/2.0, y + q, yy + k2 );
        l  = step * ( yy + k3 );
        k4 = 0.5 * step * f( x0 + step, y + l, yy + 2.0*k3 );
        
        y += step * ( yy + 1.0/3.0*( k1 + k2 + k3 ) );
        yy += 1.0/3.0 * ( k1 + 2.0*k2 + 2.0*k3 + k4 );
        x0 += step;
    }
    if (verbose) std::cout << x0 << "," << y << "," << yy << std::endl;

    return y;
}