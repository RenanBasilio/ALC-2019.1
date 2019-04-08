#include <LinearAlgebra.hpp>
#include <Exception.hpp>
#include <iostream>
#include <cmath>
#include <cstdarg>
#include <utility>

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

    for (size_t i = 0; i < aug.nrows(); i++)
    {
        double calc = 0.0;
        for (size_t j = 0; j < i; j++) {
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
            default:
                throw new std::invalid_argument("Conversion to this form is not available.");
        }
        
        A = m_t * A;
        m = m_t * m;
    }

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

Matrix solveCholeskyDecomp( Matrix A, const Matrix& b) {
    if (A.ncolumns() != A.nrows()) 
        throw new size_mismatch("Matrix A is not a square matrix.");

    Matrix L = Matrix::Identity(A.nrows());
    for (size_t i = 0; i < A.nrows(); i++) {
        double sum = 0.0;
        for (size_t j = 0; j < i; j++) {
            sum += std::pow(L.at(i, j), 2);
        }
        L.at(i,i) = std::sqrt(A.at(i,i) - sum);

        for (size_t j = i; j < A.nrows(); j++) {
            sum = 0.0;
            for (size_t k = 0; k < i; k++) {
                sum += L.at(i, k)*L.at(j, k);
            }
            L.at(j,i) = ( A.at(i, j) - sum ) / L.at(i,i);
        }
    }

    Matrix y = solveForwardSubstitution(L, b);  // Ly = b

    return solveBackSubstitution(L.transpose(), y);         // Ux = LTx = y
}

double computeResidue( const Matrix& v1, const Matrix& v2 ) {
    return computeNorm( v1 - v2 ) / computeNorm( v1 );
}

double computeResidue( const double& v1, const double& v2 ) {
    return std::fabs( v1 - v2 ) / std::fabs( v1 );
}


Matrix solveIterative( const Matrix& A, const Matrix& b, IterativeMethod m, const double tol ) {
    if (A.ncolumns() != A.nrows()) 
        throw new size_mismatch("Matrix A is not a square matrix.");
    if (A.ncolumns() != b.nrows()) 
        throw new size_mismatch("Height of matrix A does not match height of vector.");
    
    switch (m)
    {
        case IterativeMethod::Jacobi:
            if ( !A.isDiagonalDominant() ) 
                throw new does_not_converge("Matrix A is not diagonal dominant, therefore Jacobi method does not converge.");
            break;
        case IterativeMethod::GaussSeidel:
            if ( !A.isSymmetric() && !A.isDiagonalDominant() ) 
                throw new does_not_converge("Matrix A is not diagonal dominant or symmetric, therefore Jacobi method does not converge.");
    }

    Matrix curr = Matrix( b.nrows(), 1, 1.0 );
    Matrix prev = Matrix( b.nrows(), 1, 0.0 );

    while ( computeResidue(curr, prev) > tol ) {
        prev = curr;

        for ( size_t i = 0; i < b.nrows(); i++ ) {
            
            double sum = 0.0;
            switch (m)
            {
                case IterativeMethod::Jacobi: {
                    for ( size_t j = 0; j < b.nrows(); j++) {
                        if ( j != i ) sum += A.at(i, j) * prev.at(j);
                    }
                    break;
                }
                case IterativeMethod::GaussSeidel: {
                    for (size_t j = 0; j < i; j++) {
                        sum += A.at(i,j) * curr.at(j);
                    }
                    for (size_t j = i + 1; j < b.nrows(); j++) {
                        sum += A.at(i, j) * prev.at(j);
                    }
                    break;
                }
                default:
                    break;
            }

            curr.at(i) = ( b.at(i) - sum ) / A.at(i, i);
        }
    }

    return curr;
}

double computeGreatestEigenValue( const Matrix& A, const double tol ) {
    if (A.ncolumns() != A.nrows()) 
        throw new size_mismatch("Matrix A is not a square matrix.");

    Matrix vec = Matrix( A.ncolumns(), 1, 1.0 );
    double lambda = 1;
    double lambda_prev = 0;

    while ( computeResidue(lambda, lambda_prev) > tol ) {
        lambda_prev = lambda;

        vec = A * vec;
        lambda = vec.at(0);
        vec = vec / lambda;
    }

    return lambda;
}

bool checkJacobiConvergence ( const Matrix& A, const double tol, std::pair<size_t, size_t>& next ) {
    double greatest = 0.0;
    bool pass = true;
    for (size_t i = 0; i < A.nrows(); i++) {
        for (size_t j = i; j < A.ncolumns(); j++) {
            if ( j != i ) {
                if ( std::fabs(A.at(i, j)) > tol ) pass = false;
                if ( std::fabs(A.at(i, j)) > greatest ) {
                    greatest = std::fabs(A.at(i, j));
                    next.first = i;
                    next.second = j;
                }
            }
        }
    }
    return pass;
}



std::pair<Matrix, Matrix> computeEigen ( Matrix A, const double tol ) {
    if (A.ncolumns() != A.nrows()) 
        throw new size_mismatch("Matrix A is not a square matrix.");
    if (!A.isSymmetric())
        throw new does_not_converge("Matrix A is not symmetric, method won't converge.");

    Matrix X = Matrix::Identity( A.nrows() );
    std::pair<size_t, size_t> next;

    while ( !checkJacobiConvergence( A, tol, next ) ) {
        double phi = M_PI_4;
        if ( A.at(next.first, next.first) != A.at(next.second, next.second) ) {
            phi = std::atan( 2*A.at(next.first, next.second) / (A.at(next.first, next.first) - A.at(next.second, next.second)) ) / 2;
        }
        Matrix P = Matrix::Identity( A.nrows() );
        P.at(next.first, next.first) = std::cos(phi);
        P.at(next.second, next.second) = std::cos(phi);
        P.at(next.first, next.second) = -std::sin(phi);
        P.at(next.second, next.first) = std::sin(phi);

        A = P.transpose() * A * P;
        X = X * P;
    }

    return std::make_pair(A, X);
}