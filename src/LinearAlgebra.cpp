#include <LinearAlgebra.hpp>
#include <Exception.hpp>
#include <iostream>
#include <cmath>

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

Matrix ret_subs( Matrix& A, const Matrix& b) {
    A.insertColumn(A.ncolumns(), b.getColumn(0));
    return ret_subs(A);
}

// Solve an Ax=b system by gaussian elimination, returning x
Matrix gauss( Matrix& A, Matrix& b) {
    if (A.ncolumns() != A.nrows()) 
        throw new size_mismatch("Matrix A is not a square matrix.");
    if (A.ncolumns() != b.nrows()) 
        throw new size_mismatch("Height of matrix A does not match height of vector.");

    for (size_t i = 0; i < A.ncolumns(); i++) {

        // Pivotamento
        if (std::fabs(A.at(i, i)) == 0.0) {

        }
        
        Matrix m = Matrix::Identity(A.nrows());
        for (size_t j = 1; j < A.nrows(); j++) {
            m.at(j, i) = (-1)*(A.at(j, i) / A.at(i, i));
        }
        
        A = m * A;
        b = m * b;
    }

    return ret_subs(A, b);
}