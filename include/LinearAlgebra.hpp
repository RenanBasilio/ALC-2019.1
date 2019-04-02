#pragma once
#include <Matrix.hpp>

enum TransformType { RowEchelon, Diagonal };

Matrix ret_subs( const Matrix& aug );

Matrix ret_subs( Matrix A, const Matrix& b);

Matrix getTransformMatrix( Matrix A, TransformType t);

Matrix gauss( const Matrix& A, const Matrix& b);

Matrix lu_decomp (const Matrix& A, const Matrix& b);