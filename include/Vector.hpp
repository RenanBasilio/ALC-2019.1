#pragma once

#include <vector>
#include <initializer_list>
#include <cstdio>

/**
 * Esta classe representa um vetor de Álgebra Linear.
 */
class Vector
{
private:
    std::vector<double> _data;
    size_t _length;

public:
    Vector(size_t length);
    Vector(size_t length, const std::initializer_list<double> data);
    Vector(size_t length, double* data);

    /* Copy Constructor */
    Vector(const Vector& v);

    /* Assignment Operator */
    Vector& operator=(Vector other);

    friend void swap(Vector& first, Vector& second);

    ~Vector();

    /* Accessor */
    double& at(const size_t i);
    const double& at(const size_t i) const;

    /* Utility */
    size_t length() const;
};