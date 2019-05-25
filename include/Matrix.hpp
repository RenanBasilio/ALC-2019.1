#pragma once

#include <string>
#include <initializer_list>
#include <vector>
#include <cstdio>

#include <Definitions.hpp>

/**
 * Esta classe representa uma matriz para aplicações de algebra linear.
 * Os dados da matriz são armazenados no formato row-major.
 * 
 * Autor: Renan Basilio
 */
class Matrix
{
private:
    std::vector<std::vector<real>> _data;
    size_t _columns, _rows;

public:
    Matrix() {};
    explicit Matrix(const size_t rows, const size_t columns = 1, const real value = 0.0);
    //Matrix(const std::initializer_list<real> data, size_t rows = 0, size_t columns = 1);
    explicit Matrix(const std::vector<std::vector<real>> data, size_t rows = 0, size_t columns = 0);
    //Matrix(const std::initializer_list<std::initializer_list<real>> data, size_t rows = 0, size_t columns = 0);

    ~Matrix();

    /* Getters */
    size_t ncolumns() const;

    size_t nrows() const;

    /* Accessor */
    real& at(const size_t r, const size_t c = 0);

    const real& at(const size_t r, const size_t c = 0) const;

    const std::vector<real> getRow(const size_t index) const;

    std::vector<real> getColumn(const size_t index) const;

    void insertRow(const size_t position, const std::vector<real> l);

    void insertColumn(const size_t position, const std::vector<real> l);

    std::vector<real> removeRow(const size_t position);

    std::vector<real> removeColumn(const size_t position);

    void swapRow(const size_t pos1, size_t pos2);

    /* Matrix Operations */
    bool operator== (const Matrix& other) const;

    Matrix operator* (const Matrix& other) const;

    Matrix operator+ (const Matrix& other) const;

    Matrix operator- (const Matrix& other) const;

    Matrix transpose() const;

    /* Scalar operations */
    Matrix operator+ (const real s) const;
    friend Matrix operator+ (const real s, const Matrix& matrix);

    Matrix operator- (const real s) const;
    friend Matrix operator- (const real s, const Matrix& matrix);

    Matrix operator* (const real s) const;
    friend Matrix operator* (const real s, const Matrix& matrix);

    Matrix operator/ (const real s) const;
    friend Matrix operator/ (const real s, const Matrix& matrix);

    /* Properties */
    bool isDiagonalDominant() const;
    bool isSymmetric() const;

    /* Utility Methods */
    operator std::string() const;

    /* Special Matrices */
    static Matrix Identity(const size_t size);
};

Matrix operator+ (const real s, const Matrix& matrix);

Matrix operator- (const real s, const Matrix& matrix);

Matrix operator* (const real s, const Matrix& matrix);

Matrix operator/ (const real s, const Matrix& matrix);

std::ostream& operator<< (std::ostream& s, const Matrix& mtx);

real computeNorm( const Matrix& vec );