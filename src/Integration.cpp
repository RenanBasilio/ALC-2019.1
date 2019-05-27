#include <exception>
#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <Integration.hpp>
#include <Generators.hpp>

real computeIntegral( Function f, real x1, real x2, size_t pts, IntegrationMethod m ) {
    switch (m)
    {
    case IntegrationMethod::Polinomial:
        return computeIntegralPolinomial( f, x1, x2, pts );
    case IntegrationMethod::Quadrature:
        return computeIntegralQuadrature( f, x1, x2, pts );
    default:
        throw std::runtime_error("Method computeIntegral() not implemented for IntegrationMethod specified.");
        break;
    }
}

real computeIntegralPolinomial ( Function f, real a, real b, size_t pts ) {
    if (pts == 1) return f( (a + b)/2 );

    real delta = (b - a)/(pts-1.0);
    real sum = 0;

    std::vector<real> weights;
    #ifndef USE_LAGRANGE_WEIGHTS_TABLE
        weights = generateLagrangeWeights( pts );
    #else
        extern const std::vector<std::vector<real>> lagrange_weights;
        if ( pts <= lagrange_weights.size() ) weights = lagrange_weights.at( pts );
        else weights = generateLagrangeWeights( pts );
    #endif

    for ( size_t i = 0; i < pts; i++ ) {
        sum += f(a + (i*delta))*weights.at(i);
    }

    return sum;
}

real computeIntegralQuadrature ( Function f, real a, real b, size_t pts ) {
    if ( pts > 10 || pts < 1 ) throw std::runtime_error( "Pesos e Abscissas nao definidas para " + std::to_string(pts) + " pontos de integração.");
    real len = b - a;
    real sum = 0;
    
    extern const std::vector<std::vector<std::pair<real, real>>> quadrature_abscissae_weights;
    const std::vector<std::pair<real, real>> abscissae_weights = quadrature_abscissae_weights.at(pts);

    for ( size_t i = 0; i < pts; i++ ) {
        sum += f( 0.5 * (a + b + abscissae_weights.at(i).first*len) ) * abscissae_weights.at(i).second;
    }

    return (len * sum)/2;
}