#include <Matrix.hpp>
#include <Exception.hpp>
#include <sstream>
#include <iostream>

Matrix::Matrix(size_t columns, size_t rows) : 
    _columns(columns),
    _rows(rows)
{
    _data = std::vector<std::vector<double>>(rows, std::vector<double>(columns));
}

Matrix::~Matrix() {
}

std::string Matrix::toString() const {
    std::stringstream buff;

    buff << "[ ";
    for (size_t i = 0; i < _rows; i++) {
        if (i > 0) buff << "  ";
        buff << "[ ";
        for (size_t j = 0; j < _columns; j++) {
            if (j > 0) buff << ", ";
            buff << _data.at(i).at(j);
        }
        buff << " ]";
        if (i != _rows - 1) buff << "," << std::endl;
    }
    buff << " ]" << std::endl;

    return buff.str();
}