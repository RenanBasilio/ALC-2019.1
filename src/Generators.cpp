#include <Generators.hpp>
#include <LinearAlgebra.hpp>

std::vector<double> generateLagrangeWeights( int pts ) {
    double delta = 1.0/(pts-1.0);
    Matrix vandermonde = Matrix( pts, pts, 1 );
    Matrix b = Matrix( pts );

    for ( int i = 0; i < pts; i++ ) {
        for ( int j = 0; j < pts; j++) {
            vandermonde.at( i, j ) = std::pow( 0 + (j*delta), i);
        }
        b.at(i) = ( std::pow(1, i+1) - std::pow(0, i+1) ) / (i + 1);
    }

    Matrix weights = solveLUDecomp( vandermonde, b );

    std::vector<double> weights_v;
    weights_v.reserve(weights.nrows());
    for ( size_t i = 0; i < weights.nrows(); i++ ) weights_v.push_back( weights.at(i) );

    return weights_v;
}
