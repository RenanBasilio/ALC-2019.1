#include <exception>
#include <vector>
#include <tuple>
#include <iostream>
#include <Integration.hpp>
#include <Generators.hpp>

real computeIntegral( Function f, real x1, real x2, size_t pts, IntegrationMethod m ) {
    switch (m)
    {
    case IntegrationMethod::Polinomial:
        return computeIntegralPolinomial( f, x1, x2, pts );
        break;
    
    default:
        throw std::runtime_error("Method computeIntegral() not implemented for IntegrationMethod specified.");
        break;
    }
}

real computeIntegralPolinomial ( Function f, real x1, real x2, size_t pts ) {
    if (pts == 1) return f( (x1 + x2)/2 );
    else {
        real delta = (x2 - x1)/(pts-1.0);
        real sum = 0;

        #ifndef USE_LAGRANGE_WEIGHTS_TABLE
            std::vector<real> weights = generateLagrangeWeights( pts );
        #else
            extern const std::vector<std::vector<real>> lagrange_weights;
            std::vector<real> weights;
            if ( pts <= lagrange_weights.size() ) weights = lagrange_weights.at( pts );
            else weights = generateLagrangeWeights( pts );
        #endif

        for ( size_t i = 0; i < pts; i++) {
            sum += f(x1 + (i*delta))*weights.at(i);
        }

        return sum;
    }
}