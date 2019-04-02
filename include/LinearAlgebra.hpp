#pragma once
#include <Matrix.hpp>

Matrix ret_subs( const Matrix& aug );

Matrix ret_subs( Matrix& A, const Matrix& b);

Matrix gauss( Matrix& A, Matrix& b);