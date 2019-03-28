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
    Matrix(const size_t rows, const size_t columns = 1, const double value = 0.0);
    Matrix(const std::initializer_list<double> data, size_t rows = 0, size_t columns = 1);
    Matrix(const std::initializer_list<std::initializer_list<double>> data, size_t rows = 0, size_t columns = 0);

    ~Matrix();

    /* Getters */
    size_t ncolumns() const;

    size_t nrows() const;

    /* Accessor */
    double& at(const size_t i, const size_t j = 0);

    const double& at(const size_t i, const size_t j = 0) const;

    const std::vector<double> getRow(const size_t index) const;

    std::vector<double> getColumn(const size_t index) const;

    /* Matrix Operations */
    Matrix transpose() const;

    Matrix operator* (const Matrix& other) const;

    Matrix operator+ (const Matrix& other) const;

    Matrix operator- (const Matrix& other) const;

    /* Scalar operations */
    Matrix operator+ (const double s) const;
    friend Matrix operator+ (const double s, const Matrix& matrix);

    Matrix operator- (const double s) const;
    friend Matrix operator- (const double s, const Matrix& matrix);

    Matrix operator* (const double s) const;
    friend Matrix operator* (const double s, const Matrix& matrix);

    Matrix operator/ (const double s) const;
    friend Matrix operator/ (const double s, const Matrix& matrix);

    /* Utility Methods */
    std::string toString() const;
};

Matrix operator+ (const double s, const Matrix& matrix);

Matrix operator- (const double s, const Matrix& matrix);

Matrix operator* (const double s, const Matrix& matrix);

Matrix operator/ (const double s, const Matrix& matrix);