#define _USE_MATH_DEFINES
#include <cmath>

#include <LinearAlgebra.hpp>
#include <Exception.hpp>
#include <iostream>
#include <cstdarg>
#include <utility>

Matrix solveBackSubstitution( const Matrix& aug ) {
    if ( aug.ncolumns() != aug.nrows() + 1 ) throw size_mismatch("Invalid matrix size for retro substitution operation.");

    Matrix x = Matrix(aug.nrows());

    for (int i = aug.nrows() - 1; i >= 0; i--)
    {
        real calc = 0.0;
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
    if ( aug.ncolumns() != aug.nrows() + 1 ) throw size_mismatch("Invalid matrix size for forward substitution operation.");

    Matrix x = Matrix(aug.nrows());

    for (size_t i = 0; i < aug.nrows(); i++)
    {
        real calc = 0.0;
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

Matrix transformMatrix ( Form t, Matrix& A) {
    int n = 0;
    return transformMatrix( t, A, n);
}

Matrix transformMatrix( Form t, Matrix& A, int& p) {

    Matrix m = Matrix::Identity(A.nrows());
    p = 0;

    for (size_t i = 0; i < A.ncolumns(); i++) {

        // Pivotamento
        if (fabs(A.at(i, i)) == 0.0) {
            for(size_t j = i; j < A.nrows(); j++) {
                if (A.at(j, i) != 0.0) {
                    A.swapRow(i, j);
                    p++;
                    break;
                }
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
                throw std::invalid_argument("Conversion to this form is not available.");
        }
        
        A = m_t * A;
        m = m_t * m;
    }

    return m;
}

// Solve an Ax=b system by gaussian elimination, returning x
Matrix solveGaussElim ( Matrix A, const Matrix& b) {
    if (A.ncolumns() != A.nrows()) 
        throw size_mismatch("Matrix A is not a square matrix.");
    if (A.ncolumns() != b.nrows()) 
        throw size_mismatch("Height of matrix A does not match height of vector.");

    Matrix m = transformMatrix(Form::RowEchelon, A);

    return solveBackSubstitution(A, m*b);
}

Matrix solveGaussJordanElim ( Matrix A, const Matrix& b) {
    if (A.ncolumns() != A.nrows()) 
        throw size_mismatch("Matrix A is not a square matrix.");
    if (A.ncolumns() != b.nrows()) 
        throw size_mismatch("Height of matrix A does not match height of vector.");

    Matrix m = transformMatrix(Form::Diagonal, A);

    return solveBackSubstitution(A, m*b);
}

Matrix computeInverse( Matrix m ) {
    if (m.ncolumns() != m.nrows()) 
        throw size_mismatch("Matrix is not a square matrix.");

    Matrix i = transformMatrix(Form::Identity, m);

    return i;
}

Matrix solveLUDecomp( Matrix A, const Matrix& b){
    if (A.ncolumns() != A.nrows()) 
        throw size_mismatch("Matrix A is not a square matrix.");
    if (A.ncolumns() != b.nrows()) 
        throw size_mismatch("Height of matrix A does not match height of vector.");

    Matrix L = computeInverse(transformMatrix(Form::RowEchelon, A));
    Matrix y = solveForwardSubstitution(L, b);

    return solveBackSubstitution(A, y);
}

Matrix solveCholeskyDecomp( Matrix A, const Matrix& b) {
    if (A.ncolumns() != A.nrows()) 
        throw size_mismatch("Matrix A is not a square matrix.");

    Matrix L = Matrix::Identity(A.nrows());
    for (size_t i = 0; i < A.nrows(); i++) {
        real sum = 0.0;
        for (size_t j = 0; j < i; j++) {
            sum += pow(L.at(i, j), 2);
        }
        L.at(i,i) = sqrt(A.at(i,i) - sum);

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

real computeResidue( const Matrix& v1, const Matrix& v2 ) {
    return computeNorm( v1 - v2 ) / computeNorm( v1 );
}

real computeResidue( const real& v1, const real& v2 ) {
    return fabs( v1 - v2 ) / fabs( v1 );
}


Matrix solveIterative( const Matrix& A, const Matrix& b, IterativeMethod m, const real tol ) {
    if (A.ncolumns() != A.nrows()) 
        throw size_mismatch("Matrix A is not a square matrix.");
    if (A.ncolumns() != b.nrows()) 
        throw size_mismatch("Height of matrix A does not match height of vector.");
    
    switch (m)
    {
        case IterativeMethod::Jacobi:
            if ( !A.isDiagonalDominant() ) 
                throw does_not_converge("Matrix A is not diagonal dominant, therefore Jacobi method does not converge.");
            break;
        case IterativeMethod::GaussSeidel:
            if ( !A.isSymmetric() && !A.isDiagonalDominant() ) 
                throw does_not_converge("Matrix A is not diagonal dominant or symmetric, therefore Gauss-Seidel method does not converge.");
    }

    Matrix curr = Matrix( b.nrows(), 1, 1.0 );
    Matrix prev = Matrix( b.nrows(), 1, 0.0 );
    size_t iterations = 0;

    while ( computeResidue(curr, prev) > tol ) {
        iterations++;
        prev = curr;

        for ( size_t i = 0; i < b.nrows(); i++ ) {
            
            real sum = 0.0;
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

    std::cout << "Iterative method converged after " << iterations << " iterations." << std::endl;
    return curr;
}

real computeGreatestEigenValue( const Matrix& A, const real tol ) {
    if (A.ncolumns() != A.nrows()) 
        throw size_mismatch("Matrix A is not a square matrix.");

    Matrix vec = Matrix( A.ncolumns(), 1, 1.0 );
    real lambda = 1;
    real lambda_prev = 0;

    size_t iterations = 0;
    while ( computeResidue(lambda, lambda_prev) > tol ) {
        lambda_prev = lambda;

        vec = A * vec;
        lambda = vec.at(0);
        vec = vec / lambda;

        iterations++;
    }

    std::cout << "Power method converged after " << iterations << " iterations." << std::endl;
    return lambda;
}

bool checkJacobiConvergence ( const Matrix& A, const real tol, std::pair<size_t, size_t>& next ) {
    real greatest = 0.0;
    bool pass = true;
    for (size_t i = 0; i < A.nrows(); i++) {
        for (size_t j = i; j < A.ncolumns(); j++) {
            if ( j != i ) {
                if ( fabs(A.at(i, j)) > tol ) pass = false;
                if ( fabs(A.at(i, j)) > greatest ) {
                    greatest = fabs(A.at(i, j));
                    next.first = i;
                    next.second = j;
                }
            }
        }
    }
    return pass;
}



std::pair<Matrix, Matrix> computeEigen ( Matrix A, const real tol ) {
    if (A.ncolumns() != A.nrows()) 
        throw size_mismatch("Matrix A is not a square matrix.");
    if (!A.isSymmetric())
        throw does_not_converge("Matrix A is not symmetric, method won't converge.");

    Matrix X = Matrix::Identity( A.nrows() );
    std::pair<size_t, size_t> next;

    while ( !checkJacobiConvergence( A, tol, next ) ) {
        real phi = M_PI_4;
        if ( A.at(next.first, next.first) != A.at(next.second, next.second) ) {
            phi = atan( 2*A.at(next.first, next.second) / (A.at(next.first, next.first) - A.at(next.second, next.second)) ) / 2;
        }
        Matrix P = Matrix::Identity( A.nrows() );
        P.at(next.first, next.first) = cos(phi);
        P.at(next.second, next.second) = cos(phi);
        P.at(next.first, next.second) = -sin(phi);
        P.at(next.second, next.first) = sin(phi);

        A = P.transpose() * A * P;
        X = X * P;
    }

    return std::make_pair(A, X);
}

real determinant( Matrix A ) {
    if (A.ncolumns() != A.nrows()) 
        throw size_mismatch("Matrix A is not a square matrix.");

    int p;
    transformMatrix(RowEchelon, A, p);

    real det = 1.0;
    for ( size_t i = 0; i < A.nrows(); i++) {
        det *= A.at(i, i);
    }
    return pow(-1, p) * det;
}