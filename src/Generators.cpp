#include <Generators.hpp>
#include <LinearAlgebra.hpp>
#include <cmath>
#include <iostream>

std::vector<real> generateLagrangeWeights( int pts ) {
    return generateLagrangeWeights(pts, 0, 1);
}

std::vector<real> generateLagrangeWeights( int pts, real x1, real x2 ) {
    real delta = (x2 - x1)/(pts-1.0);
    Matrix vandermonde = Matrix( pts, pts, 1 );
    Matrix b = Matrix( pts );

    for ( int i = 0; i < pts; i++ ) {
        for ( int j = 0; j < pts; j++) {
            vandermonde.at( i, j ) = pow( (j*delta), i);
        }
        b.at(i) = ( pow(x2, i+1) - pow(x1, i+1) ) / (i + 1);
    }
    Matrix weights = solveLUDecomp( vandermonde, b );

    std::vector<real> weights_v;
    weights_v.reserve(weights.nrows());
    for ( size_t i = 0; i < weights.nrows(); i++ ) weights_v.push_back( weights.at(i) );

    return weights_v;
}
