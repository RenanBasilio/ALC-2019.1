#include <LinearAlgebra.hpp>
#include <Exception.hpp>
#include <iostream>

Matrix ret_subs( const Matrix& aug ) {
    if ( aug.ncolumns() != aug.nrows() + 1 ) throw new size_mismatch("Invalid matrix size for forward substitution operation.");

    Matrix x = Matrix(aug.nrows());

    for (int i = aug.nrows() - 1; i >= 0; i--)
    {
        double calc = 0.0;
        for (size_t j = aug.ncolumns() - 2; j > i; j--) {
            calc += aug.at(i, j) * x.at(j);
        }
        x.at(i) = (aug.at(i, aug.ncolumns() - 1) - calc) / aug.at(i, i);
    }

    return x;
}