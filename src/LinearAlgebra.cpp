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

Matrix ret_subs( Matrix A, const Matrix& b) {
    A.insertColumn(A.ncolumns(), b.getColumn(0));
    return ret_subs(A);
}

Matrix getTransformMatrix( Matrix A, TransformType t) {
    switch (t)
    {
        case TransformType::RowEchelon: {
                Matrix m = Matrix::Identity(A.nrows());
                for (size_t i = 0; i < A.ncolumns(); i++) {

                    // Pivotamento
                    if (std::fabs(A.at(i, i)) == 0.0) {
                        for(size_t j = i; j < A.nrows(); i++) {
                            if (A.at(j, i) != 0.0)
                                A.swapRow(i, j);
                        }
                    }
                    
                    Matrix m_t = Matrix::Identity(A.nrows());
                    for (size_t j = 1; j < A.nrows(); j++) {
                        m_t.at(j, i) = (-1)*(A.at(j, i) / A.at(i, i));
                    }
                    
                    if (i != A.ncolumns()) A = m_t * A;
                    m = m_t * m;
                }
                return m;
            }
            break;
    
        default:
            break;
    }
}



// Solve an Ax=b system by gaussian elimination, returning x
Matrix gauss( const Matrix& A, const Matrix& b) {
    if (A.ncolumns() != A.nrows()) 
        throw new size_mismatch("Matrix A is not a square matrix.");
    if (A.ncolumns() != b.nrows()) 
        throw new size_mismatch("Height of matrix A does not match height of vector.");

    Matrix m = getTransformMatrix(A, TransformType::RowEchelon);

    return ret_subs(m*A, m*b);
}

Matrix lu_decomp( Matrix& A, Matrix& b){
    if (A.ncolumns() != A.nrows()) 
        throw new size_mismatch("Matrix A is not a square matrix.");
    if (A.ncolumns() != b.nrows()) 
        throw new size_mismatch("Height of matrix A does not match height of vector.");

    Matrix m = getTransformMatrix(A, TransformType::RowEchelon);

}