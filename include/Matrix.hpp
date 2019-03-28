#pragma once

#include <string>
#include <initializer_list>
#include <vector>
#include <cstdio>

/**
 * Esta classe representa uma matriz para aplicações de algebra linear.
 * Os dados da matriz são armazenados no formato row-major.
 * 
 * Autor: Renan Basilio
 */
class Matrix
{
private:
    std::vector<std::vector<double>> _data;
    size_t _columns, _rows;

public:
    Matrix(size_t rows, size_t columns = 1);
    Matrix(const std::initializer_list<double> data, size_t rows = 0, size_t columns = 1);
    Matrix(const std::initializer_list<std::initializer_list<double>> data, size_t rows = 0, size_t columns = 0);

    ~Matrix();

    /* Accessor */
    double& at(const size_t i, const size_t j = 0);

    const double& at(const size_t i, const size_t j = 0) const;

    /* Matrix Operations */
    Matrix transpose() const;

    Matrix operator* (const Matrix& other);

    /* Utility Methods */
    std::string toString() const;
    size_t ncolumns() const;
    size_t nrows() const;
};