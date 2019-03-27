#pragma once

#include <string>
#include <initializer_list>
#include <vector>
#include <cstdio>
#include <Vector.hpp>

/**
 * Esta classe representa uma matriz quadrada para aplicações de algebra linear.
 * 
 * @author Renan Basilio
 */
class SqMatrix
{
private:
    std::vector<Vector> _data;
    size_t _size;

public:
    SqMatrix(size_t size);
    SqMatrix(size_t size, const Vector* data );
    SqMatrix(size_t size, const std::initializer_list<Vector> data);
    SqMatrix(size_t size, const std::initializer_list<std::initializer_list<double>> data);

    /* Copy Constructor */
    SqMatrix(const SqMatrix& m);

    ~SqMatrix();

    /* Accessor */
    double& at(const size_t i, const size_t j);

    const double& at(const size_t i, const size_t j) const;

    Vector& at(const size_t i);

    /* Matrix Operations */
    SqMatrix transpose() const;

    SqMatrix operator* (const SqMatrix& m);

    /* Vector Operations */
    Vector operator* (const Vector& v);

    /* Utility Methods */
    size_t size() const;
    std::string toString() const;
};
