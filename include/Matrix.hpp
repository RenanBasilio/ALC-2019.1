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
    Matrix() {};
    Matrix(const size_t rows, const size_t columns = 1, const double value = 0.0);
    Matrix(const std::vector<std::vector<double>> data, size_t rows = 0, size_t columns = 0);

    ~Matrix();

    /* Getters */
    size_t ncolumns() const;

    size_t nrows() const;

    /* Accessor */
    double& at(const size_t r, const size_t c = 0);

    const double& at(const size_t r, const size_t c = 0) const;

    const std::vector<double> getRow(const size_t index) const;

    std::vector<double> getColumn(const size_t index) const;

    void insertRow(const size_t position, const std::vector<double> l);

    void insertColumn(const size_t position, const std::vector<double> l);

    std::vector<double> removeRow(const size_t position);

    std::vector<double> removeColumn(const size_t position);

    void swapRow(const size_t pos1, size_t pos2);

    /* Matrix Operations */
    bool operator== (const Matrix& other) const;

    Matrix operator* (const Matrix& other) const;

    Matrix operator+ (const Matrix& other) const;

    Matrix operator- (const Matrix& other) const;

    Matrix transpose() const;

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
    operator std::string() const;

    /* Special Matrices */
    static Matrix Identity(const size_t size);
};

Matrix operator+ (const double s, const Matrix& matrix);

Matrix operator- (const double s, const Matrix& matrix);

Matrix operator* (const double s, const Matrix& matrix);

Matrix operator/ (const double s, const Matrix& matrix);

std::ostream& operator<< (std::ostream& s, const Matrix& mtx);

double computeNorm( const Matrix& vec );