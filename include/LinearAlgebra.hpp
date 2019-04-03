#pragma once
#include <Matrix.hpp>

enum Form { RowEchelon, Diagonal, Identity };

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
 * @return A matriz de transformação.
 */
Matrix transformMatrix ( Form t, Matrix& A );

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
Matrix solveRetroSubstitution ( const Matrix& aug );

/**
 * Resolve um sistema Ax=b por retro-substituição.
 * 
 * @param A Uma matriz quadrada.
 * @param b Um vetor de dimensão igual à da matriz A.
 * @return O vetor solução do sistema.
 */
Matrix solveRetroSubstitution ( Matrix A, const Matrix& b );

/**
 * Resolve um sistema linear por eliminação de gauss.
 * 
 * @param A Uma matriz quadrada.
 * @param b Um vetor de dimensão igual à da matriz A.
 * @return O vetor solução do sistema.
 */
Matrix solveGaussElim ( const Matrix& A, const Matrix& b );

/**
 * Resolve um sistema linear por eliminação de gauss-jordan.
 * 
 * @param A Uma matriz quadrada.
 * @param b Um vetor de dimensão igual à da matriz A.
 * @return O vetor solução do sistema.
 */
Matrix solveGaussJordanElim ( const Matrix& A, const Matrix& b );

/**
 * Resolve um sistema linear por decomposição LU.
 * 
 * @param A Uma matriz quadrada.
 * @param b Um vetor de dimensão igual à da matriz A.
 * @return O vetor solução do sistema.
 */
Matrix solveLUDecomp ( const Matrix& A, const Matrix& b );