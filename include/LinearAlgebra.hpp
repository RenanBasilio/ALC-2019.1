#pragma once
#include <Matrix.hpp>

#include <Definitions.hpp>

enum Form { RowEchelon, Diagonal, Identity };
enum IterativeMethod { Jacobi, GaussSeidel };

/**
 * A partir da matriz A, obtem uma matriz de transformação para
 * a forma t e aplica a mesma sobre A e todas as demais matrizes
 * fornecidas.
 * 
 * Todas as matrizes passadas a este método são alteradas pelo
 * mesmo.
 * 
 * @param t A forma à qual a matriz A deve ser convertida.
 * @param A A matriz a ser transformada.
 * @param p Parâmetro de saída, representa o número de pivotamentos.
 * @return A matriz de transformação.
 */
Matrix transformMatrix ( Form t, Matrix& A );
Matrix transformMatrix ( Form t, Matrix& A, int& p);

/**
 * Calcula a inversa de uma matriz.
 * 
 * @param m Uma matriz quadrada.
 * @return A matriz inversa de m.
 */
Matrix computeInverse ( Matrix m );

/**
 * Resolve um sistema Ax=b por retro-substituição.
 * 
 * @param aug A matriz aumentada.
 * @return O vetor x.
 */
Matrix solveBackSubstitution ( const Matrix& aug );

/**
 * Resolve um sistema Ax=b por substituição para frente.
 * 
 * @param aug A matriz aumentada.
 * @return O vetor x.
 */
Matrix solveForwardSubstitution ( const Matrix& aug );

/**
 * Resolve um sistema Ax=b por retro-substituição.
 * 
 * @param A Uma matriz quadrada.
 * @param b Um vetor de dimensão igual à da matriz A.
 * @return O vetor solução do sistema.
 */
Matrix solveBackSubstitution ( Matrix A, const Matrix& b );

/**
 * Resolve um sistema Ax=b por substituição para frente.
 * 
 * @param A Uma matriz quadrada.
 * @param b Um vetor de dimensão igual à da matriz A.
 * @return O vetor solução do sistema.
 */
Matrix solveForwardSubstitution ( Matrix A, const Matrix& b );

/**
 * Resolve um sistema linear por eliminação de gauss.
 * 
 * @param A Uma matriz quadrada.
 * @param b Um vetor de dimensão igual à da matriz A.
 * @return O vetor solução do sistema.
 */
Matrix solveGaussElim ( Matrix A, const Matrix& b );

/**
 * Resolve um sistema linear por eliminação de gauss-jordan.
 * 
 * @param A Uma matriz quadrada.
 * @param b Um vetor de dimensão igual à da matriz A.
 * @return O vetor solução do sistema.
 */
Matrix solveGaussJordanElim ( Matrix A, const Matrix& b );

/**
 * Resolve um sistema linear por decomposição LU.
 * 
 * @param A Uma matriz quadrada.
 * @param b Um vetor de dimensão igual à da matriz A.
 * @return O vetor solução do sistema.
 */
Matrix solveLUDecomp ( Matrix A, const Matrix& b );

/**
 * Resolve um sistema linear por decomposição de Cholesky.
 * 
 * @param A Uma matriz quadrada.
 * @param b Um vetor de dimensão igual à da matriz A.
 * @return O vetor solução do sistema.
 */
Matrix solveCholeskyDecomp ( Matrix A, const Matrix& b );

/**
 * Calcula o resíduo de entre dois vetores tal que
 * R = || v1 - v2 || / || v1 ||
 * 
 * @param v1 Um vetor coluna
 * @param v2 Outro vetor coluna
 * @return O resíduo.
 */
real computeResidue( const Matrix& v1, const Matrix& v2 );
real computeResidue( const real& v1, const real& v2 );

/**
 * Resolve um sistema linear por um método iterativo.
 * 
 * @param A Uma matriz quadrada.
 * @param b Um vetor de dimensão igual à da matriz A.
 * @param m O método iterativo a ser utilizado.
 * @param tol A tolerância do resíduo para convergência.
 * @return O vetor solução do sistema linear.
 */
Matrix solveIterative( const Matrix& A, const Matrix& b, IterativeMethod m, const real tol = 10E-5 );

/**
 * Calcula o maior autovalor através do Método de Potência
 * 
 * @param A Uma matriz quadrada.
 * @param tol A tolerância do resíduo para convergência.
 * @return O maior autovalor de A.
 */
real computeGreatestEigenValue( const Matrix& A , const real tol = 10E-5 );

/**
 * Calcula matrizes de autovalores e autovetores.
 * 
 * @param A Uma matriz quadrada.
 * @param tol A tolerância do resíduo para convergência.
 * @return Um par de matrizes no qual first é uma matriz com os autovalores
 * na diagonal principal e second é a matriz dos autovetores.
 */
std::pair<Matrix, Matrix> computeEigen( Matrix A, const real tol = 10E-5 );

/**
 * Calcula o determinante de uma matriz.
 * 
 * @param A Uma matriz quadrada.
 * @return O determinante da matriz A.
 */
real determinant( Matrix A );