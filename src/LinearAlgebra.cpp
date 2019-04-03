#include <LinearAlgebra.hpp>
#include <Exception.hpp>
#include <iostream>
#include <cmath>
#include <cstdarg>

Matrix solveBackSubstitution( const Matrix& aug ) {
    if ( aug.ncolumns() != aug.nrows() + 1 ) throw new size_mismatch("Invalid matrix size for retro substitution operation.");

    Matrix x = Matrix(aug.nrows());

    for (int i = aug.nrows() - 1; i >= 0; i--)
    {
        double calc = 0.0;
        for (int j = aug.ncolumns() - 2; j > i; j--) {
            calc += aug.at(i, j) * x.at(j);
        }
        x.at(i) = (aug.at(i, aug.ncolumns() - 1) - calc) / aug.at(i, i);
    }

    return x;
}

Matrix solveBackSubstitution( Matrix A, const Matrix& b) {
    A.insertColumn(A.ncolumns(), b.getColumn(0));
    return solveBackSubstitution(A);
}

Matrix solveForwardSubstitution( const Matrix& aug ) {
    if ( aug.ncolumns() != aug.nrows() + 1 ) throw new size_mismatch("Invalid matrix size for forward substitution operation.");

    Matrix x = Matrix(aug.nrows());

    for (int i = 0; i < aug.nrows(); i++)
    {
        double calc = 0.0;
        for (int j = 0; j < i; j++) {
            calc += aug.at(i, j) * x.at(j);
        }
        x.at(i) = (aug.at(i, aug.ncolumns() - 1) - calc) / aug.at(i, i);
    }

    return x;
}

Matrix solveForwardSubstitution( Matrix A, const Matrix& b) {
    A.insertColumn(A.ncolumns(), b.getColumn(0));
    return solveForwardSubstitution(A);
}

Matrix transformMatrix( Form t, Matrix& A) {

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
        switch (t) {
            case Form::Identity:
                m_t.at(i, i) = 1 / A.at(i, i);
            case Form::Diagonal:
                // Parte acima da diagonal principal
                for (size_t j = 0; j < i; j++) {
                    m_t.at(j, i) = (-1)*(A.at(j, i) / A.at(i, i));
                }
            case Form::RowEchelon:
                // Parte abaixo da diagonal principal
                for (size_t j = i + 1; j < A.nrows(); j++) {
                    m_t.at(j, i) = (-1)*(A.at(j, i) / A.at(i, i));
                }
                break;
        }
        
        A = m_t * A;
        m = m_t * m;
    }

    std::cout << A << std::endl;

    return m;
}

// Solve an Ax=b system by gaussian elimination, returning x
Matrix solveGaussElim ( Matrix A, const Matrix& b) {
    if (A.ncolumns() != A.nrows()) 
        throw new size_mismatch("Matrix A is not a square matrix.");
    if (A.ncolumns() != b.nrows()) 
        throw new size_mismatch("Height of matrix A does not match height of vector.");

    Matrix m = transformMatrix(Form::RowEchelon, A);

    return solveBackSubstitution(A, m*b);
}

Matrix solveGaussJordanElim ( Matrix A, const Matrix& b) {
    if (A.ncolumns() != A.nrows()) 
        throw new size_mismatch("Matrix A is not a square matrix.");
    if (A.ncolumns() != b.nrows()) 
        throw new size_mismatch("Height of matrix A does not match height of vector.");

    Matrix m = transformMatrix(Form::Diagonal, A);

    return solveBackSubstitution(A, m*b);
}

Matrix computeInverse( Matrix m ) {
    if (m.ncolumns() != m.nrows()) 
        throw new size_mismatch("Matrix is not a square matrix.");

    Matrix i = transformMatrix(Form::Identity, m);

    return i;
}

Matrix solveLUDecomp( Matrix A, const Matrix& b){
    if (A.ncolumns() != A.nrows()) 
        throw new size_mismatch("Matrix A is not a square matrix.");
    if (A.ncolumns() != b.nrows()) 
        throw new size_mismatch("Height of matrix A does not match height of vector.");

    Matrix L = computeInverse(transformMatrix(Form::RowEchelon, A));
    Matrix y = solveForwardSubstitution(L, b);

    return solveBackSubstitution(A, y);
}