#pragma once

#include <string>
#include <initializer_list>
#include <vector>
#include <cstdio>
#include <Vector.hpp>

/**
 * Esta classe representa uma matriz para aplicações de algebra linear.
 * Os dados da matriz são armazenados no formato row-major.
 * 
 * @author Renan Basilio
 */
class Matrix
{
private:
    std::vector<std::vector<double>> _data;
    size_t _columns, _rows;

public:
    Matrix(size_t _columns, size_t _rows);
    Matrix(const std::initializer_list<double> data);
    Matrix(const std::initializer_list<std::initializer_list<double>> data);

    /* Copy Constructor */
    Matrix(const Matrix& m);

    /* Assignment Operator */
    Matrix& operator=(Matrix other);

    ~Matrix();

    /* Accessor */
    double& at(const size_t i, const size_t j);

    const double& at(const size_t i, const size_t j) const;

    /* Matrix Operations */
    Matrix transpose() const;

    Matrix operator* (const Matrix& other);

    /* Utility Methods */
    size_t ncolumns() const;
    size_t nrows() const;
    std::string toString() const;
};